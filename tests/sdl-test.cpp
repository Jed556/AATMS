#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int WinMain(int argc, char const* argv[]) {
    // sdl2 code that prints hello world in the center of the interface

    GUI GUI("AATMS", 640, 480);

    Font font1(GUI.getRenderer(), "res/fonts/arialbd.ttf", 70, {255, 255, 255, 255});
    Font font2(GUI.getRenderer(), "res/fonts/arial.ttf", 40, {255, 255, 255, 255});
    font1.setText("AATMS", GUI.getWidth() / 2, (GUI.getHeight() / 2) - 40);
    font2.setText("Pls halp", GUI.getWidth() / 2, (GUI.getHeight() / 2) + 30);

    bool running = true;
    while (running) {
        running = GUI.isRunning();
        SDL_RenderClear(GUI.getRenderer());
        font1.renderCopy();
        font2.renderCopy();
        SDL_RenderPresent(GUI.getRenderer());
    }
    return 0;
}