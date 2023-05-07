#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>

#define Unique_Renderer(ptr) SDL_Renderer_PTR(ptr, sdl_deleter())
#define Unique_Window(ptr) SDL_Window_PTR(ptr, sdl_deleter())
#define Unique_Texture(ptr) SDL_Texture_PTR(ptr, sdl_deleter())

struct sdl_deleter
{
	void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
	void operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }
	void operator()(SDL_Texture* p) const { SDL_DestroyTexture(p); }
};

typedef std::unique_ptr<SDL_Window, sdl_deleter>	SDL_Window_PTR;
typedef std::unique_ptr<SDL_Texture, sdl_deleter>	SDL_Texture_PTR;
typedef std::unique_ptr<SDL_Renderer, sdl_deleter>	SDL_Renderer_PTR;




class GameWindow {
public:
	GameWindow();
	~GameWindow() = default;

	bool init();  

	SDL_Renderer_PTR createRenderer();

	void handleEvent(SDL_Event& e);
	
	void setSize(int width, int height);

	void centerOnScreen();

	std::tuple<int, int> getDimensions();
	
private:
	SDL_Window_PTR window;

	int width;
	int height;



};

class Texture {
public:
	Texture(SDL_Renderer* renderer);
	Texture(SDL_Renderer* renderer, std::string& path);
	Texture(SDL_Renderer* renderer, const char* path);
	~Texture() = default;

	bool loadFromFile(const std::string& path);
	bool loadFromFile(const char* path);

	void renderAt(int x, int y, SDL_Rect* clip, float angle, SDL_RendererFlip flip);
	std::tuple<int, int> getDimensions();


	SDL_Texture_PTR texture;
protected:
	SDL_Renderer* renderer;
	int width;
	int height;

};

class AnimatedSprite : public Texture {
public:
	AnimatedSprite(SDL_Renderer* renderer, int frames, int frame_width, int frame_height)						: Texture(renderer), frames(frames), frame_width(frame_width), frame_height(frame_height) {};
	AnimatedSprite(SDL_Renderer* renderer, std::string& path, int frames, int frame_width, int frame_height)	: Texture(renderer, path), frames(frames), frame_width(frame_width), frame_height(frame_height) {};
	AnimatedSprite(SDL_Renderer* renderer, const char* path, int frames, int frame_width, int frame_height)		: Texture(renderer, path), frames(frames), frame_width(frame_width), frame_height(frame_height) {};
	~AnimatedSprite() = default;

	void renderAt(int x, int y, float angle, SDL_RendererFlip flip, bool animated);

private:
	int frames;
	int frame_width;
	int frame_height;
	//int frame_offset;

};



class Screen {
public:
	Screen();

};


//class Renderer {
//public:
//	Renderer() = default;
//	Renderer(SDL_Renderer_PTR renderer);
//	~Renderer() = default;
//
//	//void renderTextureAt(Texture&, int x, int y);
//
//
//private:
//	SDL_Renderer_PTR renderer;
//
//};

