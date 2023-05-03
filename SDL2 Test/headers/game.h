#pragma once
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <functional>
#include "rendering.h"
#include "player.h"

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
	GameWindow windowInstance;
	SDL_Renderer_PTR renderer;
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Texture>> images;
	std::unordered_map<std::string, std::unique_ptr<Texture>> sprites;


	int current_image;
	int window_width;
	int window_height;

	enum class Screens {
		Menu,
		Game,
		Image_Cycle,
	};
	Screens current_screen;


public:
	Game();
	~Game();

	bool init();

	bool beginMainLoop();

	void logicUpdate(float delta_time);

	void loadMedia();

	void processEvents();

	void render();


};