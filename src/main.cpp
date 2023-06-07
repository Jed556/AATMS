#include <AATMS.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>

int WinMain(int argc, char const* argv[]) {
    // sdl2 code that prints hello world in the center of the interface
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("AATMS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font1 = TTF_OpenFont("res/fonts/arialbd.ttf", 70);
    TTF_Font* font2 = TTF_OpenFont("res/fonts/arial.ttf", 40);
    SDL_Color color = {255, 255, 255};
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font1, "AATMS", color);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font2, "Hello World!", color);
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect rect1;
    SDL_Rect rect2;
    rect1.x = 640 / 2 - titleSurface->w / 2;
    rect1.y = 480 / 2 - titleSurface->h / 2 - 40;
    rect1.w = titleSurface->w;
    rect1.h = titleSurface->h;
    rect2.x = 640 / 2 - textSurface->w / 2;
    rect2.y = 480 / 2 - textSurface->h / 2 + 30;
    rect2.w = textSurface->w;
    rect2.h = textSurface->h;
    SDL_FreeSurface(titleSurface);
    SDL_FreeSurface(textSurface);
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture1, NULL, &rect1);
        SDL_RenderCopy(renderer, texture2, NULL, &rect2);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    TTF_Quit();
    SDL_Quit();
    return 0;
}