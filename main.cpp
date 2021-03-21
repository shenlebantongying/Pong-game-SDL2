#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PADDLE_WIDTH = 100;

void sdl_error(const std::string &msg) {
    std::cout << "Error:" << msg << "->" << SDL_GetError() << std::endl;
    exit(-1);
}

using BALL = struct {
    SDL_Rect rect;
    int vx;
    int vy;
    int dir_x;
    int dir_y;
};

using player = struct {
    SDL_Rect pos;
    int score;
    int speed;
};


int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) sdl_error("failed to init");


    SDL_ShowCursor(SDL_DISABLE);

    SDL_Window *win = SDL_CreateWindow(
            "Pong game",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

    if (win == nullptr) sdl_error("Failed to init a window");

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

    if (ren == nullptr) {
        sdl_error("Renderer Creation failed");
        SDL_DestroyWindow(win);
        return 1;
    }


    auto paddle = SDL_Rect{0, SCREEN_HEIGHT - 10, PADDLE_WIDTH, 10};
    const Uint8 *keyState = SDL_GetKeyboardState(nullptr);// Global Keyboard handler
    int mouse_x, mouse_y;
    Uint32 last_update_time = 0;
    auto ball = BALL{SDL_Rect{0, 0, 10, 10}, 2, 2, 1, 1};

    const int bw = 3;

    auto window_bottom_border = SDL_Rect{0, SCREEN_HEIGHT, SCREEN_WIDTH, bw};
    auto window_top_border = SDL_Rect{0, 0, SCREEN_WIDTH, bw};
    auto window_left_border = SDL_Rect{0, 0, bw, SCREEN_HEIGHT};
    auto window_right_border = SDL_Rect{SCREEN_WIDTH - bw, 0, bw, SCREEN_HEIGHT};

    bool quit{};
    SDL_Event event;
    while (!quit) {


        //Render something
        SDL_RenderSetLogicalSize(ren, 640, 480);
        //Set colour of renderer
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        //Clear the screen to the set colour
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

        SDL_RenderFillRect(ren, &paddle);
        SDL_RenderFillRect(ren, &ball.rect);

        SDL_RenderFillRect(ren, &window_bottom_border);
        SDL_RenderFillRect(ren, &window_top_border);
        SDL_RenderFillRect(ren, &window_left_border);
        SDL_RenderFillRect(ren, &window_right_border);


        if (SDL_TICKS_PASSED(SDL_GetTicks(), last_update_time + 10)) {
            ball.rect.x += ball.vx * ball.dir_x;
            ball.rect.y += ball.vy * ball.dir_y;
            last_update_time = SDL_GetTicks();
        }
        //ball movement


        if (SDL_HasIntersection(&ball.rect, &window_bottom_border)) {
            std::cout << "game over" << std::endl;
        }

        if (SDL_HasIntersection(&ball.rect, &window_top_border) || SDL_HasIntersection(&ball.rect, &paddle)) {
            ball.dir_y *= -1;
        }
        if (SDL_HasIntersection(&ball.rect, &window_left_border) || SDL_HasIntersection(&ball.rect, &window_right_border)) {
            ball.dir_x *= -1;
        }

        //Show all the has been done behind the scenes
        SDL_RenderPresent(ren);

        while (SDL_PollEvent(&event)) {

            // quit conditions
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        quit = true;
                        break;
                    }
            }

            // movements
            if (keyState[SDL_SCANCODE_UP]) {
                paddle.y -= 5;
            }

            if (keyState[SDL_SCANCODE_DOWN]) {
                paddle.y += 5;
            }


            SDL_GetMouseState(&mouse_x, &mouse_y);

            if (mouse_x <= SCREEN_WIDTH - PADDLE_WIDTH / 2) {
                paddle.x = mouse_x;
            }
        }
    }


    //Clean Up
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}