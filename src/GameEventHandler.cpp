#include "GameEventHandler.h"

#include "WindowProc.h"
#include "Config.h"

/*
Copyright (c) 2024 Emerson Pinter

This file is part of Better AltTab for Skyrim <https://github.com/epinter/better-alttab>.
Licensed under LGPL-3.0 <https://www.gnu.org/licenses/lgpl-3.0.txt>.
*/

namespace betteralttab {
    void GameEventHandler::onLoad() {
        if (Config::getInstance().isDebugEnabled()) {
            spdlog::set_level(spdlog::level::debug);
            spdlog::flush_on(spdlog::level::debug);
            spdlog::set_pattern(PLUGIN_LOGPATTERN_DEBUG);
        }
        WindowProc::getInstance().installHookHwnd();
    }

    void GameEventHandler::onPostDataLoaded() {
        logger::debug("onPostDataLoaded: setting started flag");
        WindowProc::getInstance().setStarted(true);
    }
}  // namespace betteralttab