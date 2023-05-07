#pragma once
#include <SDL2/SDL.h>
#include "rendering.h"

class Player {
public:
	Player(float x, float y);

	void handleEvent(SDL_Event& e);
	
	float walk_speed;
	float base_acceleration;
	float static_friction;
	float drag;

	void move(float delta_time);

	void render();
	void setPos(float x, float y);

	std::tuple<float, float> getPos();
	void set_sprites(std::shared_ptr<AnimatedSprite> horizontal, std::shared_ptr<AnimatedSprite> vertical);


private:
	//SDL_Renderer* renderer;
	//Texture* sprite;

	std::shared_ptr<AnimatedSprite> horizontal_sprite;
	std::shared_ptr<AnimatedSprite> vertical_sprite;


	float rx, ry;

	float vx, vy;
	float ax, ay;

	

};

