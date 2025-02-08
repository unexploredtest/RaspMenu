#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "pugixml.hpp"
#include "raylib.h"

#include "common.hpp"

class NotifMenu : public MainMenu {
    public:

        NotifMenu(std::string link);

        void start() override;
        void stop() override;
        void runBackround() override;
        void stopBackround() override;
        void draw(WinSpec winSpec) override;
        bool input() override;
        std::string getPagesPath() override;

        // void setLink();

    private:

        void loadTextures();
        void unloadTextures();

        std::string downloadImage(std::string link);

        void loadFiveLatest();

        std::vector<Image> images = {};
        std::vector<std::string> titles = {};
        std::vector<bool> isUpdated = {};

        void retrieveChannel();
        std::shared_ptr<std::thread> retrieveChannelTask;

        // checkChannel();

        // std::shared_ptr<std::thread> checkChannelTask();

        std::string link;
        Texture2D emptyImage;
        const int MAX_VIDS = 5;
        unsigned int selectedPic = 0;
};