//#include <SDL2/SDL.h>
//
//
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//const int VOXEL_SIZE = 10;
//
//SDL_Window* window = NULL;
//SDL_Renderer* renderer = NULL;
//
//// Create a 2D array to represent the voxel world
//bool voxelWorld[SCREEN_WIDTH / VOXEL_SIZE][SCREEN_HEIGHT / VOXEL_SIZE] = { false };
//
//int main(int argc, char* argv[]) {
//    // Initialize SDL
//    SDL_Init(SDL_INIT_VIDEO);
//
//    // Create the window and renderer
//    window = SDL_CreateWindow("Voxel World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//    renderer = SDL_CreateRenderer(window, -1, 0);
//
//    // Main loop
//    bool running = true;
//    while (running) {
//        // Handle events
//        SDL_Event event;
//        while (SDL_PollEvent(&event)) {
//            switch (event.type) {
//            case SDL_QUIT:
//                running = false;
//                break;
//            case SDL_MOUSEBUTTONDOWN:
//                // Get the mouse position and calculate the corresponding voxel
//                int x, y;
//                SDL_GetMouseState(&x, &y);
//                int voxelX = x / VOXEL_SIZE;
//                int voxelY = y / VOXEL_SIZE;
//                // Toggle the state of the voxel
//                voxelWorld[voxelX][voxelY] = !voxelWorld[voxelX][voxelY];
//                break;
//            }
//        }
//
//        // Clear the screen
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//        SDL_RenderClear(renderer);
//
//        // Draw the voxels
//        for (int x = 0; x < SCREEN_WIDTH / VOXEL_SIZE; x++) {
//            for (int y = 0; y < SCREEN_HEIGHT / VOXEL_SIZE; y++) {
//                if (!voxelWorld[x][y]) {
//                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//                }
//                else {
//                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//                }
//                SDL_Rect rect = { x * VOXEL_SIZE, y * VOXEL_SIZE, VOXEL_SIZE, VOXEL_SIZE };
//                SDL_RenderFillRect(renderer, &rect);
//            }
//        }
//
//        // Update the screen
//        SDL_RenderPresent(renderer);
//    }
//
//    // Clean up
//    SDL_DestroyRenderer(renderer);
//    return 0;
//}
//
//

#include <memory>
#include <SDL2/SDL.h>
#include "headers/game.h"


int main(int argc, char* argv[]){

	auto game_instance = std::make_unique<Game>();
	game_instance->load_media();
	game_instance->begin_main_loop();
	return 0;
}

