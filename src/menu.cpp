
#include "menu.hpp"


#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

void DrawFB(int width, int height) {
    unsigned short MPixels[width*height];

    // glReadPixels(0,0,width,height, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, &MPixels);
    unsigned short SPixels[width*height];
    for(int h=0; h<height; h++) {
        for(int w=0; w<width; w++) {
            int mh = height - h - 1;
            SPixels[width*h + w] = MPixels[width*mh + w];
        }
    }

    FILE* fptr;
    fptr = fopen("/dev/fb1", "wb+");

    // checking if the file is opened successfully
    if (fptr == nullptr) {
        return;
    }

    fwrite(SPixels,sizeof(SPixels),1,fptr);
    fclose(fptr);
}


int getIntFromPage(Page page) {
    return static_cast<int>(page);
}

int getMaxPages() {
    return static_cast<int>(Page::MAX);
}

void loadPagesIcon(std::vector<std::shared_ptr<MainMenu>> pages, std::vector<Texture2D>& PagesIcon) {
    for(auto& pageObject: pages) {
        PagesIcon.push_back(LoadTexture(pageObject->getPagesPath().data()));
    }
}

void unloadPagesIcon(std::vector<Texture2D> PagesIcon) {
    for(auto& pageText: PagesIcon) {
        UnloadTexture(pageText);
    }
}

void runPagesBackground(std::vector<std::shared_ptr<MainMenu>> pages) {
    for(auto& page: pages) {
        page->runBackround();
    }
}

void stopPagesBackground(std::vector<std::shared_ptr<MainMenu>> pages) {
    for(auto& page: pages) {
        page->stopBackround();
    }
}

void drawSideBar(std::vector<std::shared_ptr<MainMenu>> pages, std::vector<Texture2D> PagesIcon, int currentPageIndex) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int iconWidth = screenWidth / 8;
    int iconHeight = screenHeight / 6;

    for(int i = 0; i < pages.size(); i++) {
        Rectangle srcRec = {0.0f, 0.0f, PagesIcon[i].width, PagesIcon[i].height};
        Rectangle desRec = {0.0f, iconWidth*i, iconWidth, iconHeight};
        Vector2 org = {0.0f, 0.0f};
        if(i == currentPageIndex) {
            // DrawTexture(PagesIcon[i], 0, 40*i, ORANGE);
            DrawTexturePro(PagesIcon[i], srcRec, desRec, org, 0, ORANGE);
        } else {
            DrawTexturePro(PagesIcon[i], srcRec, desRec, org, 0, WHITE);
        }
    }
}


void drawAbout() {


}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
void runApp(int screenWidth, int screenHeight) {
    std::vector<std::shared_ptr<MainMenu>> pages {
        std::shared_ptr<MainMenu>(new HomeMenu()),
        std::shared_ptr<MainMenu>(new RickMenu()),
        std::shared_ptr<MainMenu>(new PicsMenu("pics")),
    };
    runPagesBackground(pages);
    std::vector<Texture2D> pagesIcon = {};

    Vector2 offset = {screenWidth / 8, 0.0f};

    int frameCounter = 0;
    InitWindow(screenWidth, screenHeight, "Raspberry Pi Menu");
    loadPagesIcon(pages, pagesIcon);

    int currentPageIndex = 0;
    int pagesCount = pages.size();
    std::shared_ptr<MainMenu> currentMenu = pages[currentPageIndex];
    currentMenu->start();

    SetTargetFPS(60);   
    while (!WindowShouldClose())
    {
        if(currentMenu->input()) {
            // Update
            if(IsKeyPressed(KEY_DOWN)) {
                currentPageIndex = currentPageIndex + 1;
                if(currentPageIndex >= pagesCount) {
                    currentPageIndex = 0;
                }
                // currentPage = static_cast<Page>(pageNumber);
                // unloadEverything();
            }

            if(IsKeyPressed(KEY_UP)) {
                currentPageIndex = currentPageIndex - 1;
                if(currentPageIndex < 0) {
                    currentPageIndex = pagesCount - 1;
                }
                // currentPage = static_cast<Page>(pageNumber);
                // unloadEverything();
            }

            currentMenu->stop();
            currentMenu = pages[currentPageIndex];
            currentMenu->start();
        }
        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(WHITE);

            if(!currentMenu->fullScreen) {
                drawSideBar(pages, pagesIcon, currentPageIndex);
            }
            currentMenu->draw(offset);

        EndDrawing();
        // DrawFB(320, 240);
        frameCounter++;
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // unloadEverything();
    currentMenu->stop();
    unloadPagesIcon(pagesIcon);
    stopPagesBackground(pages);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}