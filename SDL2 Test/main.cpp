#include <memory>
#include <SDL2/SDL.h>
#include "headers/game.h"


int main(int argc, char* argv[]){

	auto game_instance = std::make_unique<Game>();
	game_instance->loadMedia();
	game_instance->init();
	game_instance->beginMainLoop();
	return 0;
}

