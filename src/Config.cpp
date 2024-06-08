#include "Config.h"
#include "SimpleIni.h"

namespace betteralttab {
    Config::Config() {
        CSimpleIni ini;
        ini.SetQuotes(true);
        ini.SetAllowKeyOnly(false);
        ini.SetUnicode(true);
        ini.SetMultiKey(false);
        std::string fileName = std::string("Data\\SFSE\\Plugins\\").append(CONFIG_FILE);

        bool save = false;
        if (ini.LoadFile(fileName.c_str()) == 0) {
            debugEnabled = ini.GetBoolValue(INI_SECTION, OPT_DEBUG, debugEnabled);
        } else {
            logger::error("Can't open config file '{}'. Trying to create a new.", CONFIG_FILE);
        }

        if (!ini.KeyExists(INI_SECTION, OPT_DEBUG)) {
            ini.SetBoolValue(INI_SECTION, OPT_DEBUG, debugEnabled, nullptr, false);
            save = true;
        }

        if (save) {
            ini.SaveFile(fileName.c_str());
        }

        logger::info("Config: {}='{}';", OPT_DEBUG, debugEnabled);
    }

    Config& Config::getInstance() {
        static Config instance;
        return instance;
    }

    bool Config::isDebugEnabled() {
        return debugEnabled;
    }

    bool Config::isCursorEnabled() {
        return cursorEnabled;
    }

    void Config::setCursorEnabled(bool b) {
        cursorEnabled = b;
    }
}  // namespace betteralttab