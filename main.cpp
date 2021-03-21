#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init() Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow(
            "Hello world",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640, 480,
            0);

    if (win == nullptr) {
        std::cerr << "SDL_CreateWindow() Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //Create and init the renderer
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
    if (ren == nullptr) {
        std::cerr << "SDL_CreateRenderer() Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
        return 1;
    }

    bool quit{};
    SDL_Event event;
    while (!quit) {
        SDL_PumpEvents();

        //Render something
        SDL_RenderSetLogicalSize(ren, 640, 480);

        //Set colour of renderer
        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);

        //Clear the screen to the set colour
        SDL_RenderClear(ren);

        //Show all the has been done behind the scenes
        SDL_RenderPresent(ren);


        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
        }
    }

    //Clean Up
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}