#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

/* TODO: creepy font rendering
 */

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PADDLE_WIDTH = 100;
const SDL_Color White = {255, 255, 255};

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

int main(int argc, char **argv) {

    // [Init]
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

    if (ren == nullptr) sdl_error("Renderer Creation failed");
    TTF_Init();


    // [Rects]
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    auto paddle = SDL_Rect{0, SCREEN_HEIGHT - 10, PADDLE_WIDTH, 10};

    const int border_width = 3;
    auto window_bottom_border = SDL_Rect{0, SCREEN_HEIGHT, SCREEN_WIDTH, border_width};
    auto window_top_border = SDL_Rect{0, 0, SCREEN_WIDTH, border_width};
    auto window_left_border = SDL_Rect{0, 0, border_width, SCREEN_HEIGHT};
    auto window_right_border = SDL_Rect{SCREEN_WIDTH - border_width, 0, border_width, SCREEN_HEIGHT};


    auto ball = BALL{SDL_Rect{10, 10, 10, 10},
                     4, 4,
                     1, 1};

    // [Vars]
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    int mouse_x;
    Uint32 last_update_time = 0;
    int score{0};
    bool quit{};


    // [Font]
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    TTF_Font *sans_font = TTF_OpenFont("OpenSans-Regular.ttf", 50);
    SDL_Surface *textSurface;
    SDL_Texture *textTexture;
    SDL_Rect text_rect;


    SDL_Event event;
    while (!quit) {
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

            SDL_GetMouseState(&mouse_x, nullptr);
            if (mouse_x <= SCREEN_WIDTH - PADDLE_WIDTH / 2) {
                paddle.x = mouse_x;
            }
        }

        // Set whole screen to black
        SDL_RenderSetLogicalSize(ren, 640, 480);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        // All following would be white
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderFillRect(ren, &paddle);
        SDL_RenderFillRect(ren, &ball.rect);
        SDL_RenderFillRect(ren, &window_bottom_border);
        SDL_RenderFillRect(ren, &window_top_border);
        SDL_RenderFillRect(ren, &window_left_border);
        SDL_RenderFillRect(ren, &window_right_border);

        // ball movement
        if (SDL_TICKS_PASSED(SDL_GetTicks(), last_update_time + 5)) {
            // Passed means if A reached B, (Not the time passed)
            ball.rect.x += ball.vx * ball.dir_x;
            ball.rect.y += ball.vy * ball.dir_y;
            last_update_time = SDL_GetTicks();
        }

        // Collision detection
        if (SDL_HasIntersection(&ball.rect, &window_bottom_border)) {
            std::cout << "game over:" << score << std::endl;
            break;
        }

        if (SDL_HasIntersection(&ball.rect, &window_top_border)) {
            ball.dir_y *= -1;
        }

        if (SDL_HasIntersection(&ball.rect, &paddle)) {
            ball.dir_y *= -1;
            score++;
            ;
        }

        if (SDL_HasIntersection(&ball.rect, &window_left_border) || SDL_HasIntersection(&ball.rect, &window_right_border)) {
            ball.dir_x *= -1;
        }

        // Update text
        textSurface = TTF_RenderText_Blended(sans_font, ("Score: " + std::to_string(score)).c_str(), White);
        textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
        SDL_RenderCopy(ren, textTexture, nullptr, &text_rect);
        text_rect = SDL_Rect{50, 50, textSurface->w, textSurface->h};

        //Show all the has been done behind the scenes
        SDL_RenderPresent(ren);
    }

    //Clean Up
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}