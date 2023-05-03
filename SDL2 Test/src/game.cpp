#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>
#include <functional>
#include <filesystem>
//namespace fs = std::filesystem;

#include "../headers/game.h"
#include "../headers/rendering.h"
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600


Game::Game() : windowInstance() {
    this->isRunning = true;
    
    this->windowInstance.init();
    this->renderer = this->windowInstance.createRenderer();

    

    this->current_image = 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        printf("SDL_Image could not initialize! SDL_Error: %s\n", SDL_GetError());
    }



}




Game::~Game() {
    IMG_Quit();
    SDL_Quit();
}

bool Game::init() {

    auto [window_width, window_height] = this->windowInstance.getDimensions();

    this->player = std::make_unique<Player>(window_width / 2, window_height / 2);
    return true;
}


bool Game::beginMainLoop() {

    double TICK_RATE = 1.0 / 60.0; // 60 FPS
    double nextTick = SDL_GetTicks() / 1000.0; // Start Time
    double accumulatedTime = 0.0;

    while (isRunning) {
        double currentTime = SDL_GetTicks();
        float delta_time = currentTime - nextTick;
        accumulatedTime += delta_time;
        nextTick = currentTime;

        processEvents();

        while (accumulatedTime >= TICK_RATE) {
            logicUpdate(delta_time);
            accumulatedTime -= TICK_RATE;
        }
        render();
    }


	return true;
}





void Game::logicUpdate(float delta_time) {
    this->player->move(delta_time);
    auto [xpos, ypos] = this->player->getPos();
    auto [window_width, window_height] = this->windowInstance.getDimensions();


    float new_x = xpos;
    float new_y = ypos;
    if (xpos < 0) { new_x = 0; }
    else if (xpos > window_width) { new_x = window_width; }

    if (ypos < 0) { new_y = 0; }
    else if (ypos > window_height) { new_y = window_height; }
    this->player->setPos(new_x, new_y);
}


void Game::loadMedia() {
    auto path = "media";
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::string file_path = entry.path().generic_string();
        auto texture = std::make_unique<Texture>(this->renderer.get());
        texture->loadFromFile(file_path);
        this->images.push_back(std::move(texture));
    }

    this->sprites["smug"] = std::make_unique<Texture>(this->renderer.get(), "sprites/smug.png");
    this->sprites["player"] = std::make_unique<Texture>(this->renderer.get(), "sprites/player.png");




}

void Game::processEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {

        switch (e.type) {
        case SDL_QUIT:
        {
            this->isRunning = false;
            std::cout << "SDL QUIT" << std::endl;
            break;
        }
        case SDL_WINDOWEVENT:
        {
            this->windowInstance.handleEvent(e);
        }
        break;
        case SDL_KEYDOWN:
        {   
            switch (e.key.keysym.sym) {
            case SDLK_SPACE:
            {
                auto len = this->images.size();
                if (this->current_image + 1 == len) {
                    this->current_image = 0;
                }
                else {
                    this->current_image++;
                }
            }
            break;
            case SDLK_ESCAPE:
            {
                this->isRunning = false;
            }
            break;
            }
        }
        break;



        }

        this->player->handleEvent(e);
    }
}


void Game::render() {
    SDL_RenderClear(this->renderer.get());

    static int old_width, old_height;
    int new_width, new_height;
    std::tie(new_width, new_height) = this->images.at(this->current_image)->getDimensions();

    //SDL_QueryTexture(.get(), NULL, NULL, &new_width, &new_height);

    if (new_width != old_width || new_height != old_height) {
        old_width = new_width;
        old_height = new_height;
        //SDL_HideWindow(this->window.get());
        this->windowInstance.setSize(old_width, old_height);
        this->windowInstance.centerOnScreen();
        printf("%d, %d\n", old_width, old_height);

        //SDL_ShowWindow(this->window.get());

    }
    this->images.at(this->current_image)->renderAt(0, 0, NULL, 0, SDL_FLIP_NONE);
    this->player->render(this->sprites["player"].get());
    //this->images.at(3).get()


    //SDL_RenderCopy(this->renderer.get(), this->images.at(this->current_image)->texture.get(), NULL, NULL);
    SDL_RenderPresent(this->renderer.get());
    
}
