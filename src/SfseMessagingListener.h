

class SfseMessagingListener {
protected:
    SfseMessagingListener() = default;

private:
    SfseMessagingListener(const SfseMessagingListener&) = delete;
    SfseMessagingListener& operator=(const SfseMessagingListener&) = delete;

public:
    ~SfseMessagingListener() = default;

    // This plugin is finishing load.
    virtual void onLoad(){};

    // All plugins have finished running SFSEPlugin_Load.
    virtual void onPostLoad(){};

    // All kPostLoad message handlers have run.
    virtual void onPostPostLoad(){};

    // All plugins have loaded, main menu is now active.
    virtual void onPostDataLoaded(){};

    // All plugins have loaded and all PostDataLoad events have handled
    virtual void onPostPostDataLoaded(){};


    template <class T>
    auto registerListener() {
        if (!SFSE::GetMessagingInterface()->RegisterListener([](SFSE::MessagingInterface::Message* message) {
                switch (message->type) {
                    case SFSE::MessagingInterface::kPostLoad:
                        T::getInstance().onPostLoad();
                        break;
                    case SFSE::MessagingInterface::kPostPostLoad:
                        T::getInstance().onPostPostLoad();
                        break;
                    case SFSE::MessagingInterface::kPostDataLoad:
                        T::getInstance().onPostDataLoaded();
                        break;
                    case SFSE::MessagingInterface::kPostPostDataLoad:
                        T::getInstance().onPostPostDataLoaded();
                        break;
                }
            })) {
            SFSE::stl::report_and_fail("Unable to register message listener.");
        }
    }
};
