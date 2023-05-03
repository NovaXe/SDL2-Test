#include <SDL2/SDL.h>
#include "player.h"
#define Sign(x) (x > 0) ? 1 : ((x < 0) ? -1 : 0)

Player::Player(float x, float y): rx(x), ry(y), vx(0), vy(0), ax(0), ay(0)
{
	//this->renderer = renderer;
    this->walk_speed = 10; // m/s
    this->base_acceleration = 0.015; // m/s^2
    this->static_friction = 0.012; // m/s^2
    this->kinetic_friction = 0.014;
}



void Player::handleEvent(SDL_Event& e)
{
    int dir = 0;
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        dir = 1;
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        dir = -1;
    }
    //dir = 1;

    switch (e.key.keysym.sym) {
    case SDLK_w:
    {
        ay -= base_acceleration * dir;
    }
    break;
    case SDLK_a:
    {
        ax -= base_acceleration * dir;
    }
    break;
    case SDLK_s:
    {
        ay += base_acceleration * dir;
    }
    break;
    case SDLK_d:
    {
        ax += base_acceleration * dir;
    }
    break;



    }
}

void Player::move(float delta_time)
{
    static float old_x = rx;
    static float old_y = ry;

    float accel_x = 0;
    float accel_y = 0;
    if (vx > 0) {
        accel_x = ax - kinetic_friction;
    }
    else if (vx < 0) {
        accel_x = ax + kinetic_friction;
    }
    else {
        accel_x = ax;
    }

    if (vy > 0) {
        accel_y = ay - kinetic_friction;
    }
    else if (vy < 0) {
        accel_y = ay + kinetic_friction;
    }
    else {
        accel_y = ay;
    }

    
    /*vx = (rx - old_x) / delta_time;
    vy = (ry - old_y) / delta_time;
    old_x = rx;
    old_y = ry;*/


    rx += vx * delta_time + accel_x * 0.5 * pow(delta_time, 2);
    ry += vy * delta_time + accel_y * 0.5 * pow(delta_time, 2);

    
}



void Player::render(Texture* sprite)
{
    auto [width, height] = sprite->getDimensions();
    static int frame = 0;
    int tot_frames = 2;



    SDL_Rect clips[4] = {
        {0, 0, 64, 64},
        {64, 0, 64, 64},
        {128, 0, 64, 64},
        {192, 0, 64, 64},
    };

    int clip = 0;
    if (this->ax != 0.0f) {
        clip = 2 + frame;
        printf("%d\r", frame);
    }
    else {
        frame = 0;
        clip = 0;
    }

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (this->ax < 0) {
        flip = SDL_FLIP_HORIZONTAL;
    }

    frame++;
    if (frame / 2 > tot_frames) {
        frame = 0;
    }
    sprite->renderAt(rx - clips[clip].w/2, ry - clips[clip].h / 2, &clips[clip], 0, flip);
}

void Player::setPos(float x, float y)
{
    rx = x;
    ry = y;
}
std::tuple<float, float> Player::getPos() {
    return std::tuple<float, float>(rx, ry);
}

