#include "rick.hpp"


RickMenu::RickMenu() {
}

void RickMenu::start() {
    this->currentRickFrame = 0;
    this->loadTextures();
}

void RickMenu::stop() {
    this->unloadTextures();
}

void RickMenu::runBackround() {
}

void RickMenu::stopBackround() {
}

void RickMenu::draw(Vector2 offset = {0.0f, 0.0f}) {
    if(this->currentRickFrame <= this->RICK_FRAME_DURATION) {
        int currentFrame = (this->currentRickFrame / 6) % 20;
        DrawTexture(this->texts[currentFrame], 0, 0, WHITE);

        this->currentRickFrame++;
    } else {
        DrawText("You got Rick Rolled!", 120, 120, 20, BLACK);
    }

}

bool RickMenu::input() {
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)) {
        return true;
    } else {
        return false;
    }
}

void RickMenu::loadTextures() {
    for(int i = 0; i < 20; i++) {
        char rickPath[50];
        sprintf(rickPath, "assests/rick/frame_%02d_delay-0.1s.png", i);
        Texture2D frameText = LoadTexture(rickPath);
        this->texts.push_back(frameText);
    }
}

void RickMenu::unloadTextures() {
    for(int i = 0; i < 20; i++) {
        UnloadTexture(this->texts[i]);
    }
    this->texts = {};
}

std::string RickMenu::getPagesPath() {
    return "assests/rick_40x40.png";
}