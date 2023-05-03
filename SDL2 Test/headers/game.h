#pragma once
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <functional>
#include "rendering.h"


//#define SDL_Window_PTR std::unique_ptr<SDL_Surface, std::function<void(SDL_Window*)>>
//typedef std::unique_ptr<SDL_Window,		std::function<void(SDL_Window*)>> SDL_Window_PTR;
//typedef std::unique_ptr<SDL_Surface,	std::function<void(SDL_Surface*)>> SDL_Surface_PTR;
//typedef std::unique_ptr<SDL_Renderer,	std::function<void(SDL_Renderer*)>> SDL_Renderer_PTR;


typedef std::unique_ptr<SDL_Window, sdl_deleter>	SDL_Window_PTR;
typedef std::unique_ptr<SDL_Surface, sdl_deleter>	SDL_Surface_PTR;
typedef std::unique_ptr<SDL_Renderer, sdl_deleter>	SDL_Renderer_PTR;
typedef std::unique_ptr<SDL_Texture, sdl_deleter>	SDL_Texture_PTR;



class Game {
private:
	bool isRunning;
	SDL_Window_PTR window;
	SDL_Renderer_PTR renderer;
	std::vector<SDL_Texture_PTR> images;
	

	int current_image;
	int window_width;
	int window_height;


public:
	Game();
	~Game();

	bool begin_main_loop();

	void logic_update();

	void load_media();

	void process_events();

	void render();


};