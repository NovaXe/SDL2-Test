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
	float kinetic_friction;

	void move(float delta_time);

	void render(Texture* sprite);
	void setPos(float x, float y);

	std::tuple<float, float> getPos();


private:
	//SDL_Renderer* renderer;
	//Texture* sprite;
	float rx, ry;

	float vx, vy;
	float ax, ay;

	

};

