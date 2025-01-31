#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>
#include <filesystem>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "raylib.h"

#include "common.hpp"

namespace fs = std::filesystem;

class PicsMenu : public MainMenu {
    public:

        PicsMenu(std::string picsPath);

        void start() override;
        void stop() override;
        void runBackround() override;
        void stopBackround() override;
        void draw(Vector2 offset) override;
        bool input() override;
        std::string getPagesPath() override;

    private:
        // static const int screenWidth = 320;
        // static const int screenHeight = 240;
        // static const int MAX_PICS = 20;
        static const int pics_hiz = 2;
        static const int pic_ver = 3;

        void loadTextures();
        void unloadTextures();

        int currentStartPic = 0;
        int maxPicCount = 0;
        void loadPics(int lower, int upper);
        void unloadPics();
        std::string picsPath;

        std::vector<Texture2D> currentPics = {};
};

inline bool ends_with(std::string const & value, std::string const & ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
