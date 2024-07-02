#include "WindowProc.h"
#include <detours/detours.h>
#include "Config.h"

/*
Copyright (c) 2024 Emerson Pinter

This file is part of Better AltTab for Starfield <https://github.com/epinter/better-alttab-sf>.
Licensed under LGPL-3.0 <https://www.gnu.org/licenses/lgpl-3.0.txt>.
*/

namespace betteralttab {
    WindowProc &WindowProc::getInstance() {
        static WindowProc instance;
        return instance;
    }

    void WindowProc::setHwnd(HWND h) {
        if (hwnd != h) {
            logger::debug("hwnd changed: from {:X} to {:X}", (uint64_t) hwnd, (uint64_t) h);
            hwnd = h;
            installHookWndProc();
        }
    }

    CURSORINFO WindowProc::getCursorInfo() {
        CURSORINFO cursorInfo{};
        cursorInfo.cbSize = sizeof(CURSORINFO);
        GetCursorInfo(&cursorInfo);
        return cursorInfo;
    }

    int WindowProc::setCursorState(bool state) {
        int cursorCount = ShowCursor(state);
        cursorFlag = getCursorInfo().flags;
        return cursorCount;
    }

    bool WindowProc::isCursorVisible() {
        return getCursorInfo().flags == CURSOR_SHOWING;
    }

    bool WindowProc::isCursorOverWindow() {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        HWND underCursor = WindowFromPoint(cursorPos);
        return underCursor == hwnd;
    }

    void WindowProc::hideCursor() {
        if (GetForegroundWindow() != hwnd)
            return;

        bool cursorVisible = isCursorVisible();
        bool cursorOverWindow = isCursorOverWindow();

        logger::debug("(hideCursor) cursor state - visible:{}; overGameWindow:{};", cursorVisible, cursorOverWindow);

        if (cursorVisible && cursorOverWindow) {
            int cursorCount = setCursorState(false);
            logger::debug("(hideCursor) ShowCursor count:{};", cursorCount);
        }
    }

    bool WindowProc::showCursor() {
        if (GetForegroundWindow() == hwnd)
            return false;

        bool cursorVisible = isCursorVisible();

        logger::debug("(showCursor) cursor state - visible:{};", cursorVisible);

        if (!cursorVisible) {
            int cursorCount = setCursorState(true);
            logger::debug("(showCursor) ShowCursor count:{};", cursorCount);
            return true;
        }

        return false;
    }

    void WindowProc::setStarted(bool b) {
        started = b;
    }

    LRESULT CALLBACK WindowProc::windowProc(HWND h, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        if (WindowProc::getInstance().started && h == WindowProc::getInstance().hwnd) {
            if (uMsg == WM_ACTIVATEAPP) {
                WORD active = LOWORD(wParam);
                if (active == 1) {
                    logger::debug("window active");
                    WindowProc::getInstance().hideCursor();
                } else {
                    logger::debug("window inactive");
                    WindowProc::getInstance().showCursor();
                }
                logger::debug("hwnd:0x{:X}; uMsg:{}; wParam:{}; lParam:{};", reinterpret_cast<std::uintptr_t>(h), uMsg, wParam, lParam);
            } else if (uMsg == WM_SETCURSOR) {
                if (LOWORD(lParam) == 1 && cursorFlag == CURSOR_SHOWING && GetForegroundWindow() == h) {
                    logger::debug("WM_SETCURSOR: cursor is over game window, hiding it");
                    if (WindowProc::getInstance().isCursorVisible()) {
                        WindowProc::getInstance().setCursorState(false);
                    }
                }
                return DefWindowProc(h, WM_SETCURSOR, wParam, lParam);
            }
        }

        return CallWindowProc(reinterpret_cast<WNDPROC>(original), h, uMsg, wParam, lParam);
    }

    bool WindowProc::installHookWndProc() {
        original = SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(windowProc));

        if (original != 0) {
            logger::info("WindowProc hook installed");
            return true;
        }

        logger::error("Failed to hook WindowProc");
        return false;
    }

    void WindowProc::funcHwnd(uint64_t param1) {
        WindowProc::getInstance().setHwnd(reinterpret_cast<HWND>(param1));
        origFuncHwnd(param1);
    }

    bool WindowProc::installHookHwnd() {
        REL::Relocation function = REL::Relocation<uintptr_t>{REL::ID{OFFSET_FUNC_HWND}};
        origFuncHwnd = function.address();
        if (DetourTransactionBegin() == NO_ERROR && DetourUpdateThread(GetCurrentThread()) == NO_ERROR &&
            DetourAttach(&reinterpret_cast<PVOID &>(origFuncHwnd), funcHwnd) == NO_ERROR && DetourTransactionCommit() == NO_ERROR) {
            logger::info("hook installed at address 0x{:08X}", function.offset());
            return true;
        }

        logger::error("Failed to hook at address 0x{:08X}", function.offset());
        return false;
    }
}  // namespace betteralttab