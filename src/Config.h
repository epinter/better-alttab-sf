namespace betteralttab {
    class Config {
    private:
        explicit Config();
        Config(Config&) = delete;
        Config& operator=(Config&&) = delete;
        void operator=(Config&) = delete;

        bool debugEnabled = false;
        static constexpr const char* CONFIG_FILE = "BetterAltTab.ini";
        static constexpr const char* INI_SECTION = "General";
        static constexpr const char* OPT_DEBUG = "Debug";

    public:
        [[nodiscard]] static Config& getInstance();
        bool isDebugEnabled();
    };
}  // namespace betteralttab