#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <tuple>
#include <string>

#include "../headers/rendering.h"


#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600


GameWindow::GameWindow()
{
	this->window.reset(nullptr);
	this->width = 0;
	this->height = 0;
}


bool GameWindow::init()
{
	SDL_Window* new_window = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (new_window != NULL) {
		this->width = DEFAULT_WINDOW_WIDTH;
		this->height = DEFAULT_WINDOW_HEIGHT;

		this->window = Unique_Window(new_window);
	}
	return new_window != NULL;
}

SDL_Renderer_PTR GameWindow::createRenderer()
{
	SDL_Renderer* new_renderer = SDL_CreateRenderer(this->window.get(), -1, SDL_RENDERER_ACCELERATED);

	return Unique_Renderer(new_renderer);
	//return SDL_Renderer_PTR(new_renderer, sdl_deleter());
}

void GameWindow::handleEvent(SDL_Event& e)
{
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
}

void GameWindow::setSize(int width, int height)
{
	SDL_SetWindowSize(this->window.get(), width, height);
	this->width = width;
	this->height = height;
}

void GameWindow::centerOnScreen() {
	SDL_SetWindowPosition(this->window.get(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}


std::tuple<int, int> GameWindow::getDimensions()
{
	return std::tuple<int, int>(this->width, this->height);
}


// Texture Wrapper Class Implementation


Texture::Texture(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	this->texture.reset(nullptr);
	this->width = 0;
	this->height = 0;

}

Texture::Texture(SDL_Renderer* renderer, std::string& path) : Texture(renderer)
{
	this->loadFromFile(path);
}

Texture::Texture(SDL_Renderer* renderer, const char* path) : Texture(renderer)
{
	this->loadFromFile(path);
}

bool Texture::loadFromFile(const std::string& path)
{
	return this->loadFromFile(path.c_str());
}

bool Texture::loadFromFile(const char* path)
{
	//The final texture
	SDL_Texture* new_texture = NULL;

	//Load image at specified path
	SDL_Surface* loaded_surface = IMG_Load(path);
	if (loaded_surface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
		return false;
	}
	else
	{
		SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
		//Create texture from surface pixels
		new_texture = SDL_CreateTextureFromSurface(this->renderer, loaded_surface);
		if (new_texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		else {
			this->width = loaded_surface->w;
			this->height = loaded_surface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loaded_surface);
	}
	this->texture = Unique_Texture(new_texture);
	return true;
}

void Texture::renderAt(int x, int y, SDL_Rect* clip, float angle=0, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
	SDL_Rect quad = { x, y, width, height };
	if (clip != NULL) {
		quad.w = clip->w;
		quad.h = clip->h;
	}

	SDL_RenderCopyEx(this->renderer, this->texture.get(), clip, &quad, angle, NULL, flip);
}

std::tuple<int, int> Texture::getDimensions()
{
	return std::tuple<int, int>(this->width, this->height);
}



//Renderer::Renderer(SDL_Renderer_PTR renderer)
//{
//	this->renderer = renderer;
//}

//void Renderer::renderTextureAt(Texture& texture, int x, int y)
//{
//	auto [width, height] = texture.getDimensions();
//	SDL_Rect quad{x,y, width, height};
//	SDL_RenderCopy(this->renderer.get(), , NULL, NULL);
//
//}
