#include <SDL2/SDL.h>
#include "player.h"
#define Sign(x) (x > 0) ? 1 : ((x < 0) ? -1 : 0)

Player::Player(float x, float y): rx(x), ry(y), vx(0), vy(0), ax(0), ay(0)
{
	//this->renderer = renderer;
    this->walk_speed = 10; // m/s
    this->base_acceleration = 0.005; // m/s^2
    this->static_friction = 0.012; // m/s^2
    this->drag = 0.014;
}

void Player::set_sprites(std::shared_ptr<AnimatedSprite> horizontal, std::shared_ptr<AnimatedSprite> vertical) {
    if (horizontal != NULL) {
        this->horizontal_sprite = horizontal;
    }

    if (vertical != NULL) {
        this->vertical_sprite = vertical;
    }

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

    accel_x = ax - drag * vx;
    accel_y = ay - drag * vy;


    //if (vx > 0) {
    //    accel_x = ax - drag;
    //}
    //else if (vx < 0) {
    //    accel_x = ax + drag;
    //}
    //else {
    //    accel_x = ax;
    //}

    //if (vy > 0) {
    //    accel_y = ay - drag;
    //}
    //else if (vy < 0) {
    //    accel_y = ay + drag;
    //}
    //else {
    //    accel_y = ay;
    //}




    
    /*vx = (rx - old_x) / delta_time;
    vy = (ry - old_y) / delta_time;
    old_x = rx;
    old_y = ry;*/


    vx = delta_time * accel_x;
    vy = delta_time * accel_y;


    rx += vx * delta_time + accel_x * 0.5 * pow(delta_time, 2);
    ry += vy * delta_time + accel_y * 0.5 * pow(delta_time, 2);

    

    
}



void Player::render()
{
    //SDL_RendererFlip flip = SDL_FLIP_NONE;
    //if (this->ax < 0) {
    //    flip = SDL_FLIP_HORIZONTAL;
    //}
    static bool last_dir_vert = false;
    
    if (std::abs(this->vy) > std::abs(this->vx)) {
        last_dir_vert = true;
    }
    else if  (std::abs(this->vy) < std::abs(this->vx)) {
        last_dir_vert = false;
    }
    

    bool vert_animated = bool(this->vy);
    bool horiz_animated = bool(this->vx);




    if (last_dir_vert) {
        this->vertical_sprite->renderAt(rx-32, ry-32, 0, SDL_FLIP_NONE, vert_animated);
    }
    else {
        this->horizontal_sprite->renderAt(rx-32, ry-32, 0, SDL_FLIP_NONE, horiz_animated);
    }

}





void Player::setPos(float x, float y)
{
    rx = x;
    ry = y;
}
std::tuple<float, float> Player::getPos() {
    return std::tuple<float, float>(rx, ry);
}

