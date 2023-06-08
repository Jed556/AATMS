#include "../interface.h"

GUI::GUI(std::string title, int width, int height) {
    this->width = width;
    this->height = height;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Window* GUI::getWindow() const {
    return window;
}
SDL_Renderer* GUI::getRenderer() const {
    return renderer;
}

int GUI::getWidth() const {
    return width;
}

int GUI::getHeight() const {
    return height;
}

int GUI::isRunning() {
    bool running = true;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;
    }
    return running;
}
