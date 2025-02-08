#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <ctime>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "raylib.h"

#include "rick.hpp"
#include "home.hpp"
#include "pics.hpp"
#include "notif.hpp"
#include "common.hpp"

enum Page {
    Home,
    Rick,
    Pics,
    // About,
    // Get rid of this
    MAX
};

// struct WinSpec {
//     Vector2 resolution;
//     Vector2 offset;
// };

int getIntFromPage(Page page);
int getMaxPages();

void drawSideBar(std::vector<Texture2D> PagesIcon, Page currentPage);
void runApp(int screenWidth = 320, int screenHeight = 240);