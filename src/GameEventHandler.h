#pragma once
#include "SfseMessagingListener.h"

namespace betteralttab {
    class GameEventHandler : public SfseMessagingListener {
    private:
        GameEventHandler() = default;
        GameEventHandler(const GameEventHandler&) = delete;
        GameEventHandler& operator=(const GameEventHandler&) = delete;

    public:
        [[nodiscard]] static GameEventHandler& getInstance() {
            static GameEventHandler instance;
            return instance;
        }

        void onLoad() override;
    };

}  // namespace betteralttab
