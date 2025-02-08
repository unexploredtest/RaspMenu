#include "notif.hpp"


NotifMenu::NotifMenu(std::string link) {
    this->link = link;
}

void NotifMenu::start() {

    this->isUpdated = std::vector<bool>(5, false);

    std::shared_ptr<std::thread> retrieveChannelTask(new std::thread(&NotifMenu::retrieveChannel, this));
    this->retrieveChannelTask = retrieveChannelTask;

    this->emptyImage = LoadTexture("assests/empty_image.png");
}

void NotifMenu::stop() {
    this->retrieveChannelTask->join();
}

void NotifMenu::runBackround() {
}

void NotifMenu::stopBackround() {
}

void NotifMenu::draw(WinSpec winSpec) {
    const int screenWidth = winSpec.resolution.x;
    const int screenHeight = winSpec.resolution.y;
    Vector2 offset = winSpec.offset;

    Vector2 org = {0.0f, 0.0f};
    Rectangle desRec = {offset.x, 0, screenWidth - offset.x, screenHeight-50};
    if(this->isUpdated[selectedPic]) {
        Rectangle srcRec = {0.0f, 0.0f, this->images[selectedPic].width, this->images[selectedPic].height};
        Texture2D text = LoadTextureFromImage(this->images[selectedPic]);
        DrawTexturePro(text, srcRec, desRec, org, 0, WHITE);
        DrawText(this->titles[selectedPic].data(), offset.x + 5, screenHeight - 30, 10, BLACK);
    } else {
        Rectangle srcRec = {0.0f, 0.0f, this->emptyImage.width, this->emptyImage.height};
        DrawTexturePro(this->emptyImage, srcRec, desRec, org, 0, WHITE);
        DrawText("NOT DOWNLOADED", offset.x + 5, screenHeight - 30, 20, BLACK);
    }
}

bool NotifMenu::input() {
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
            this->fullScreen = false;
        }

        if(IsKeyPressed(KEY_RIGHT)) {
            if(this->selectedPic < this->MAX_VIDS - 1) {
                this->selectedPic++;
            }
        }

        if(IsKeyPressed(KEY_LEFT)) {
            if(this->selectedPic > 0) {
                this->selectedPic--;
            }
        }

        return false;
    }
}

void NotifMenu::retrieveChannel() {
    cpr::Response response = cpr::Get(cpr::Url{this->link}, cpr::Timeout{10000});

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(response.text.data());

    if (!result) {
        return;
    }

    int index = 0;
    for (pugi::xml_node entry: doc.child("feed").children("entry")) {
        if(index >= this->MAX_VIDS) break;

        std::string title = entry.child("title").child_value();
        std::string imageLink = entry.child("content").child("div").child("a").child("img").attribute("src").value();

        std::cout << imageLink << std::endl;

        std::string imageData = downloadImage(imageLink);

        
        Image image = LoadImageFromMemory(".jpg", reinterpret_cast<unsigned char*>(imageData.data()), imageData.size());
        // Texture2D thumbnailText = LoadTextureFromImage(image);

        this->titles.push_back(title);
        this->images.push_back(image);
        // this->isUpdated.push_back(true);
        this->isUpdated[index] = true;
        index++;
    }

}

std::string NotifMenu::downloadImage(std::string link) {
    cpr::Response response = cpr::Get(cpr::Url{link}, cpr::Timeout{10000});

    return response.text;
}

void NotifMenu::loadTextures() {
    
}

void NotifMenu::unloadTextures() {
    // this->unloadPics();
}

std::string NotifMenu::getPagesPath() {
    return "assests/play_40x40.png";
}