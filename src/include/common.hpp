#pragma once


class MainMenu {
    public:
        MainMenu() {};
        virtual void runBackround() = 0;
        virtual void stopBackround() = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void draw(Vector2 offset) = 0;
        virtual bool input() = 0;
        virtual std::string getPagesPath() = 0;
        
        // For background processes
        bool keepRunning = true;
        bool fullScreen = false;
};