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

struct HomeText {
    Texture2D WiFiCTex;
    Texture2D WiFiDTex;
    Texture2D sunny;
    Texture2D cloudy;
    Texture2D rainy;
};

struct WeatherData {
    float temp;
    bool isRaining;
    bool isCloudy;
};

class HomeMenu : public MainMenu {
    public:

        HomeMenu();
        ~HomeMenu();

        void start() override;
        void stop() override;
        void runBackround() override;
        void stopBackround() override;
        void draw(Vector2 offset) override;
        bool input() override;
        std::string getPagesPath() override;

        bool isThereWeather = false;
        bool isThereConnection = false;
        std::shared_ptr<std::thread> weatherUpdateTask;
        std::shared_ptr<std::thread> connectionUpdateTask;
        WeatherData currentWeather;
        HomeText homeText;  

    private:
        // static const int screenWidth = 320;
        // static const int screenHeight = 240;
        void loadTextures();
        void unloadTextures();
        
        void connectionUpdate();
        void weatherUpdate(float latitude, float longitude);

        bool getConnection();
        void getWatherData(float latitude, float longitude);
};

