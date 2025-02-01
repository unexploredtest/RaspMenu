#include "home.hpp"

HomeMenu::HomeMenu() {

}

HomeMenu::~HomeMenu() {

}

void HomeMenu::runBackround() {
    std::shared_ptr<std::thread> weatherUpdateTask(new std::thread(&HomeMenu::weatherUpdate, this, 30, 30));

    // std::thread connectionUpdateTask(connectionUpdate);
    std::shared_ptr<std::thread> connectionUpdateTask(new std::thread(&HomeMenu::connectionUpdate, this));
    this->weatherUpdateTask = weatherUpdateTask;
    this->connectionUpdateTask = connectionUpdateTask;
}

void HomeMenu::stopBackround() {
    this->keepRunning = false;
    
    this->connectionUpdateTask->join();
    this->weatherUpdateTask->join();
}

void HomeMenu::start() {
    this->loadTextures();
    // homeData.homeText = loadHomeTextures();
    // std::thread weatherUpdateTask(weatherUpdate, 30, 30);

}

void HomeMenu::draw(WinSpec winSpec) {
    const int screenWidth = winSpec.resolution.x;
    const int screenHeight = winSpec.resolution.y;

    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    char currentTime[30];
    char currentDate[30];
    sprintf(currentTime, "%02d:%02d", now->tm_hour, now->tm_min);
    // For some reason the month number returned is one less than the actual month
    // (Perhaps it starts from 0?) so we add it with 1
    sprintf(currentDate, "%02d/%02d", (now->tm_mon)+1, now->tm_mday);

    DrawText(currentTime, 70, 5, 30, BLACK);
    DrawText(currentDate, 170, 5, 30, BLACK);

    if(isThereConnection) {
        DrawTexture(homeText.WiFiCTex, screenWidth - 40, 0, BLACK);
    } else {
        DrawTexture(homeText.WiFiDTex, screenWidth - 40, 0, BLACK);
    }

    if(isThereWeather) {
        // Show temperature
        char temp[10];
        sprintf(temp, "%.1f C", currentWeather.temp);
        DrawText(temp, 120, 180, 30, BLACK);

        // Show whether it's sunny, cloudy or rainy
        Texture2D currentText;
        if(currentWeather.isRaining) {
            currentText = homeText.rainy;
        } else if(currentWeather.isCloudy) {
            currentText = homeText.cloudy;
        } else {
            currentText = homeText.sunny;
        }

        DrawTexture(currentText, 120, 70, WHITE);


    }
}

bool HomeMenu::input() {
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)) {
        return true;
    } else {
        return false;
    }
}

void HomeMenu::loadTextures() {
    HomeText homeText;

    homeText.WiFiCTex = LoadTexture("assests/WiFiC_40x40.png");
    homeText.WiFiDTex = LoadTexture("assests/WiFiD_40x40.png");
    homeText.sunny = LoadTexture("assests/sunny_100x100.png");
    homeText.cloudy = LoadTexture("assests/cloudy_100x70.png");
    homeText.rainy = LoadTexture("assests/rainy_100x71.png");

    this->homeText = homeText;
}

void HomeMenu::stop() {
    this->unloadTextures();
}

void HomeMenu::unloadTextures() {
    UnloadTexture(this->homeText.WiFiCTex);
    UnloadTexture(this->homeText.WiFiDTex);
    UnloadTexture(this->homeText.sunny);
    UnloadTexture(this->homeText.cloudy);
    UnloadTexture(this->homeText.rainy);
}

bool HomeMenu::getConnection() {
    cpr::Response response = cpr::Get(cpr::Url{"https://google.com", }, cpr::Timeout{10000});
    if(response.status_code == 200) {
        return true;
    } else {
        return false;
    }
}

void HomeMenu::connectionUpdate() {
    while(this->keepRunning) {
        this->isThereConnection = getConnection();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void HomeMenu::getWatherData(float latitude, float longitude) {
    char url[150];
    sprintf(url, "https://api.open-meteo.com/v1/forecast?latitude=%.2f&longitude=%.2f&current=temperature_2m,rain,cloud_cover", 
        latitude, longitude);

    cpr::Response response = cpr::Get(cpr::Url{url}, cpr::Timeout{10000});

    if(response.status_code != 200) {
        return;
    }
    
    nlohmann::json ex1 = nlohmann::json::parse(response.text);

    float temp;
    float rain;
    float cloud;

    ex1["current"]["temperature_2m"].get_to(temp);
    ex1["current"]["rain"].get_to(rain);
    ex1["current"]["cloud_cover"].get_to(cloud);

    bool isRaining;
    if(rain > 0) {
        isRaining = true;
    } else {
        isRaining = false;
    }

    bool isCloudy;
    if(cloud > 0) {
        isCloudy = true;
    } else {
        isCloudy = false;
    }

    this->isThereWeather = true;
    this->currentWeather = WeatherData{temp, isRaining, isCloudy};
}

void HomeMenu::weatherUpdate(float latitude, float longitude) {
    while(this->keepRunning) {
        this->getWatherData(latitude, longitude);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

std::string HomeMenu::getPagesPath() {
    return "assests/home_40x40.png";
}
