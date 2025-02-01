#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "raylib.h"

#include "common.hpp"

class RickMenu : public MainMenu {
    public:

        RickMenu();

        void start() override;
        void stop() override;
        void runBackround() override;
        void stopBackround() override;
        void draw(WinSpec winSpec) override;
        bool input() override;
        std::string getPagesPath() override;

    private:
        // static const int screenWidth = 320;
        // static const int screenHeight = 240;

        void loadTextures();
        void unloadTextures();

        std::vector<Texture2D> texts = {};
        int currentRickFrame = 0;
        static const int RICK_FRAME_DURATION = 120;
};

