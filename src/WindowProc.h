#pragma once

/*
Copyright (c) 2024 Emerson Pinter

This file is part of Better AltTab for Starfield <https://github.com/epinter/better-alttab>.
Licensed under LGPL-3.0 <https://www.gnu.org/licenses/lgpl-3.0.txt>.
*/

namespace betteralttab {
    class WindowProc {
    private:
        static constexpr int OFFSET_FUNC_HWND = 202998;
        HWND hwnd = 0;
        bool started = false;
        static inline int cursorFlag = -1;

        static LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        static inline LONG_PTR original;
        static void funcHwnd(uint64_t param1);
        static inline REL::Relocation<decltype(funcHwnd)> origFuncHwnd;

        void setHwnd(HWND h);
        CURSORINFO getCursorInfo();
        bool installHookWndProc();
        void hideCursor();
        bool showCursor();
        int setCursorState(bool state);
        bool isCursorVisible();
        bool isCursorOverWindow();

    public:
        [[nodiscard]] static WindowProc& getInstance();
        bool installHookHwnd();
        void setStarted(bool b);
    };
}  // namespace betteralttab