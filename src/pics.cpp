#include "pics.hpp"


PicsMenu::PicsMenu(std::string picsPath) {
    this->picsPath = picsPath;
}

void PicsMenu::start() {
    this->loadPics(0, pic_ver*pics_hiz);
}

void PicsMenu::stop() {

}

void PicsMenu::runBackround() {
}

void PicsMenu::stopBackround() {
}

void PicsMenu::draw(WinSpec winSpec) {
    // each y is 80, we have 3 ys
    // each x is 130, we have 2 xs
    const int screenWidth = winSpec.resolution.x;
    const int screenHeight = winSpec.resolution.y;
    Vector2 offset = winSpec.offset;

    // float offset = 40.0f;
    // if(this->fullScreen) {
    //     offset = 0.0f;
    // }

    float pic_height = screenHeight / pics_hiz;
    float pic_width = (screenWidth - offset.x) / pic_ver;

    if(this->isSelected) {
        Rectangle srcRec = {0.0f, 0.0f, this->currentPics[this->selectedPic].width, this->currentPics[this->selectedPic].height};
        Rectangle desRec = {0, 0, screenWidth, screenHeight};
        Vector2 org = {0.0f, 0.0f};
        DrawTexturePro(this->currentPics[this->selectedPic], srcRec, desRec, org, 0, WHITE);
        return;
    }

    int i = 0;
    for(int y = 0; y < pics_hiz; y++) {
        for(int x = 0; x < pic_ver; x++) {
            if(i < this->currentPics.size()) {
                Rectangle srcRec = {0.0f, 0.0f, this->currentPics[i].width, this->currentPics[i].height};
                Rectangle desRec = {offset.x + pic_width*x, pic_height*y, pic_width, pic_height};
                Vector2 org = {0.0f, 0.0f};
                if(this->fullScreen && i == this->selectedPic) {
                    DrawTexturePro(this->currentPics[i], srcRec, desRec, org, 0, RED);
                } else {
                    DrawTexturePro(this->currentPics[i], srcRec, desRec, org, 0, WHITE);
                }
                i++;
            }
        }
    }
}

bool PicsMenu::input() {
    if(!this->fullScreen){
        if(IsKeyPressed(KEY_ENTER)) {
            this->fullScreen = true;
            return false;
        }

        if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)) {
            return true;
        } else {
            return false;
        }
    }

    if(this->fullScreen) {

        
        if(IsKeyPressed(KEY_BACKSPACE)) {
            if(this->isSelected) {
                this->isSelected = false;
            } else {
                this->fullScreen = false;
            }
        }

        if(IsKeyPressed(KEY_ENTER)) {
            if(!this->isSelected) {
                this->isSelected = true;
            }
        }

        if(IsKeyPressed(KEY_RIGHT)) {
            if((this->currentStartPic + 1)*(pic_ver*pics_hiz) <= this->maxPicCount) {
                this->currentStartPic++;
                this->unloadPics();
                this->loadPics(this->currentStartPic*(pic_ver*pics_hiz), (this->currentStartPic+1)*(pic_ver*pics_hiz));
            }
        }

        if(IsKeyPressed(KEY_LEFT)) {
            if(this->currentStartPic > 0) {
                this->currentStartPic--;
                this->unloadPics();
                this->loadPics(this->currentStartPic*(pic_ver*pics_hiz), (this->currentStartPic+1)*(pic_ver*pics_hiz));
            }
        }

        if(IsKeyPressed(KEY_W)) {
            this->selectedPic = (this->selectedPic - this->pic_ver) % (this->pic_ver * this->pics_hiz);
        }

        if(IsKeyPressed(KEY_S)) {
            this->selectedPic = (this->selectedPic + this->pic_ver) % (this->pic_ver * this->pics_hiz);
        }

        if(IsKeyPressed(KEY_D)) {
            this->selectedPic = (this->selectedPic + 1) % (this->pic_ver * this->pics_hiz);
        }

        if(IsKeyPressed(KEY_A)) {
            this->selectedPic = (this->selectedPic - 1) % (this->pic_ver * this->pics_hiz);
        }


        return false;
    }
}

void PicsMenu::loadPics(int lower, int upper) {

    // std::cout << "l: " << lower << "h: " << upper << std::endl;

    this->currentPics.clear();

    int i = 0;
    for (const auto& entry : fs::directory_iterator(this->picsPath)) {
        std::string filename = entry.path().filename();
        if(fs::is_directory(entry.path()) || (!ends_with(filename, ".png") && !ends_with(filename, ".jpg"))) {
            continue;
        }
        if(i >= upper || i < lower) {
            i++;
            continue;
        } else {
            i++;
            this->currentPics.push_back(LoadTexture((this->picsPath + "/" + filename).data()));
        }
    }
    this->maxPicCount = i;
}

void PicsMenu::unloadPics() {
    for(auto& i: this->currentPics) {
        UnloadTexture(i);
    }
    this->currentPics.clear();
}


void PicsMenu::loadTextures() {
    
}

void PicsMenu::unloadTextures() {
    this->unloadPics();
}

std::string PicsMenu::getPagesPath() {
    return "assests/pics.png";
}