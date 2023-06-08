#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>
#include <array>

class GUI {
   private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;

   public:
    GUI(std::string, int, int);
    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;
    int getWidth() const;
    int getHeight() const;
    int isRunning();
};

class Font {
   private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Rect rect;
    TTF_Font* font;
    SDL_Color color;

   public:
    Font(SDL_Renderer*, std::string, int, std::array<Uint8, 4>);
    void setText(std::string, int x, int y);
    void renderCopy();
    void setFont(std::string, int);
    void setColor(std::array<Uint8, 4>);
    void setRed(Uint8);
    void setGreen(Uint8);
    void setBlue(Uint8);
    void setAlpha(Uint8);
};

#endif  // INTERFACE_H