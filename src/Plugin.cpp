using namespace SFSE;
using namespace SFSE::log;
using namespace SFSE::stl;

#include "Plugin.h"
#include "GameEventHandler.h"

namespace betteralttab {
    void initializeLogging() {
        auto path = log_directory();
        if (!path) {
            report_and_fail("Can't find SFSE log directory");
        }
        *path /= fmt::format("{}.log"sv, Plugin::Name);

        std::shared_ptr<spdlog::logger> log;
        if (IsDebuggerPresent()) {
            log = std::make_shared<spdlog::logger>("Global", std::make_shared<spdlog::sinks::msvc_sink_mt>());
        } else {
            log = std::make_shared<spdlog::logger>("Global", std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true));
        }
        log->set_level(spdlog::level::info);
        log->flush_on(spdlog::level::info);

        spdlog::set_default_logger(std::move(log));
        spdlog::set_pattern(PLUGIN_LOGPATTERN_DEFAULT);
    }
}  // namespace mutebg

using namespace betteralttab;

DLLEXPORT bool SFSEAPI SFSEPlugin_Load(const SFSE::LoadInterface* sfse) {
    initializeLogging();
    Init(sfse);
    logger::info("'{} {}' is loading, game version '{}'...", Plugin::Name, Plugin::Version.string(), sfse->RuntimeVersion().string());

    GameEventHandler::getInstance().registerListener<GameEventHandler>();

    GameEventHandler::getInstance().onLoad();

    logger::info("{} has finished loading.", Plugin::Name);
    return true;
}
