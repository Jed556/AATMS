#include "../interface.h"

/**
 * @brief Construct a new Font object
 *
 * @param renderer The renderer to use
 * @param fontPath Path of font file
 * @param size Size of the font
 * @param color RGBA color {red, green, blue, alpha} [0 - 255]
 */
Font::Font(SDL_Renderer* renderer, std::string fontPath, int size, std::array<Uint8, 4> color) {
    this->renderer = renderer;
    setFont(fontPath, size);
    setColor(color);
}

/**
 * @brief Ready the text to display
 *
 * @param text Text to display
 * @param x Position on the x axis
 * @param y Position on the y axis
 */
void Font::setText(std::string text, int x, int y) {
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect = {x - (surface->w / 2), y - (surface->h / 2), surface->w, surface->h};
    SDL_FreeSurface(surface);
}

/**
 * @brief Display the text
 *
 */
void Font::renderCopy() {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

/**
 * @brief Create SDL Font
 *
 * @param fontPath Path of font file
 * @param size Size of the font
 */
void Font::setFont(std::string fontPath, int size) {
    font = TTF_OpenFont(fontPath.c_str(), size);
}

/**
 * @brief Set font color
 *
 * @param color RGBA color {red, green, blue, alpha} [0 - 255]
 */
void Font::setColor(std::array<Uint8, 4> color) {
    this->color = {color[0], color[1], color[2], color[3]};
}

/**
 * @brief Set font red value [0 - 255]
 *
 * @param red
 */
void Font::setRed(Uint8 red) {
    this->color.r = red;
}

/**
 * @brief Set font green value [0 - 255]
 *
 * @param green
 */
void Font::setGreen(Uint8 green) {
    this->color.g = green;
}

/**
 * @brief Set font blue value [0 - 255]
 *
 * @param blue
 */
void Font::setBlue(Uint8 blue) {
    this->color.b = blue;
}

/**
 * @brief Set font alpha value [0 - 255]
 *
 * @param alpha
 */
void Font::setAlpha(Uint8 alpha) {
    this->color.a = alpha;
}