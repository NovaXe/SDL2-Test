#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>
#include <functional>


#include "../headers/game.h"
#include "../headers/rendering.h"
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600


Game::Game() {
    this->isRunning = true;
    SDL_Window* new_window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    this->window = SDL_Window_PTR(new_window, sdl_deleter());

    SDL_Renderer* new_renderer = SDL_CreateRenderer(this->window.get(), -1, SDL_RENDERER_ACCELERATED);
    if (new_renderer == NULL) {
        std::cout << "Error renderer creation";
        throw 4;
    }
    else {
        SDL_SetRenderDrawColor(this->renderer.get(), 0x00, 0xF0, 0xF0, 0xFF);
    }
    this->renderer = SDL_Renderer_PTR(new_renderer, sdl_deleter());
    
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

bool Game::begin_main_loop() {

    double TICK_RATE = 1.0 / 60.0; // 60 FPS
    double nextTick = SDL_GetTicks() / 1000.0; // Start Time
    double accumulatedTime = 0.0;

    while (isRunning) {
        double currentTime = SDL_GetTicks();
        accumulatedTime += (currentTime - nextTick);
        nextTick = currentTime;

        process_events();

        while (accumulatedTime >= TICK_RATE) {
            logic_update();
            accumulatedTime -= TICK_RATE;
        }
        render();
    }


	return true;
}





void Game::logic_update() {

}

void Game::load_media() {
    auto ryuko_sur = IMG_Load("media/ryuko.jpg");
    auto astro_sur = IMG_Load("media/astroneer.png");


    if (ryuko_sur == NULL || astro_sur == NULL) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
    }

    auto ryuko = SDL_Texture_PTR(SDL_CreateTextureFromSurface(this->renderer.get(), ryuko_sur), sdl_deleter());
    auto astro = SDL_Texture_PTR(SDL_CreateTextureFromSurface(this->renderer.get(), astro_sur), sdl_deleter());
    SDL_FreeSurface(ryuko_sur);
    SDL_FreeSurface(astro_sur);

    this->images.push_back(std::move(ryuko));
    this->images.push_back(std::move(astro));




}

void Game::process_events() {
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
            switch (e.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                {
                    //int mWidth = e.window.data1;
                    //int mHeight = e.window.data2;
                    //SDL_SetWindowSize(this->window.get(), mWidth, mHeight);
                    //SDL_RenderPresent(this->renderer.get());
                }
                break;
                case SDL_WINDOWEVENT_EXPOSED:
                {
                    //SDL_RenderPresent(this->renderer.get());
                }
                break;
            }

        case SDL_KEYDOWN:
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
                    break;
                }





            }




        }

    }
}


void Game::render() {
    SDL_RenderClear(this->renderer.get());

    static int old_width, old_height;
    int new_width, new_height;
    SDL_QueryTexture(this->images.at(this->current_image).get(), NULL, NULL, &new_width, &new_height);

    if (new_width != old_width || new_height != old_height) {
        old_width = new_width;
        old_height = new_height;
        //SDL_HideWindow(this->window.get());
        SDL_SetWindowSize(this->window.get(), old_width, old_height);
        SDL_SetWindowPosition(this->window.get(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

        //SDL_ShowWindow(this->window.get());

    }

    

    SDL_RenderCopy(this->renderer.get(), this->images.at(this->current_image).get(), NULL, NULL);
    SDL_RenderPresent(this->renderer.get());
    
}
