#pragma once

struct WinSpec {
    Vector2 resolution;
    Vector2 offset;
};

class MainMenu {
    public:
        MainMenu() {};
        virtual void runBackround() = 0;
        virtual void stopBackround() = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void draw(WinSpec winSpec) = 0;
        virtual bool input() = 0;
        virtual std::string getPagesPath() = 0;
        
        // For background processes
        bool keepRunning = true;
        bool fullScreen = false;
};