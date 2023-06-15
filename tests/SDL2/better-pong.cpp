#include <SDL.h>
#include <SDL_image.h>

#include <array>
#include <cmath>
#include <iostream>

const int WINDOW_WIDTH = 850;
const int WINDOW_HEIGHT = 600;
const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 100;
const int BALL_RADIUS = 10;
const int PADDLE_SPEED = 5;
const int BALL_BASE_SPEED = 3;
const float VELOCITY_INCREASE_FACTOR = 1.1f;

bool isRunning = true;
bool isPaused = false;
bool isDebug = false;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int paddle1Y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
int paddle2Y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
float ballX = WINDOW_WIDTH / 2;
float ballY = WINDOW_HEIGHT / 2;
float ballVelocityX = BALL_BASE_SPEED;
float ballVelocityY = BALL_BASE_SPEED;
int bounceCount = 0;

// function prototypes
void handleEvents();
void movePaddle1Up();
void movePaddle1Down();
void movePaddle2Up();
void movePaddle2Down();
void update();
void render();

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE) {
                isPaused = !isPaused;  // Toggle pause
            }
            if (event.key.keysym.sym == SDLK_SLASH) {
                isDebug = !isDebug;  // Toggle pause
            }
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
        }
    }
}

void movePaddle1Up() {
    paddle1Y -= PADDLE_SPEED;
    if (paddle1Y < 0) {
        paddle1Y = 0;
    }
}

void movePaddle1Down() {
    paddle1Y += PADDLE_SPEED;
    if (paddle1Y > WINDOW_HEIGHT - PADDLE_HEIGHT) {
        paddle1Y = WINDOW_HEIGHT - PADDLE_HEIGHT;
    }
}

void movePaddle2Up() {
    paddle2Y -= PADDLE_SPEED;
    if (paddle2Y < 0) {
        paddle2Y = 0;
    }
}

void movePaddle2Down() {
    paddle2Y += PADDLE_SPEED;
    if (paddle2Y > WINDOW_HEIGHT - PADDLE_HEIGHT) {
        paddle2Y = WINDOW_HEIGHT - PADDLE_HEIGHT;
    }
}

void update() {
    if (isPaused) return;
    ballX += ballVelocityX;
    ballY += ballVelocityY;

    // Check collision with paddles
    if (ballX <= PADDLE_WIDTH + 20 && ballY + BALL_RADIUS >= paddle1Y && ballY <= paddle1Y + PADDLE_HEIGHT) {
        ballVelocityX = std::abs(ballVelocityX) * VELOCITY_INCREASE_FACTOR;
        bounceCount++;
    } else if (ballX >= WINDOW_WIDTH - PADDLE_WIDTH - BALL_RADIUS - 20 && ballY + BALL_RADIUS >= paddle2Y && ballY <= paddle2Y + PADDLE_HEIGHT) {
        ballVelocityX = -std::abs(ballVelocityX) * VELOCITY_INCREASE_FACTOR;
        bounceCount++;
    }

    // Check collision with walls
    if (ballY <= 0 || ballY >= WINDOW_HEIGHT - BALL_RADIUS) {
        ballVelocityY = -ballVelocityY;
    }

    // Check for scoring
    if (ballX <= 0 || ballX >= WINDOW_WIDTH - BALL_RADIUS) {
        // Reset ball position
        ballX = WINDOW_WIDTH / 2;
        ballY = WINDOW_HEIGHT / 2;
        // Reverse ball direction
        ballVelocityX = BALL_BASE_SPEED;
        ballVelocityY = BALL_BASE_SPEED * std::pow(VELOCITY_INCREASE_FACTOR, bounceCount);
        bounceCount = 0;  // Reset bounce count
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Draw paddles
    SDL_Rect paddle1Rect = {20, paddle1Y, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle1Rect);

    SDL_Rect paddle2Rect = {WINDOW_WIDTH - PADDLE_WIDTH - 20, paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_RenderFillRect(renderer, &paddle2Rect);

    // Draw ball
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int ballCenterX = ballX + BALL_RADIUS / 2;
    int ballCenterY = ballY + BALL_RADIUS / 2;
    for (int y = ballY; y < ballY + BALL_RADIUS; y++) {
        for (int x = ballX; x < ballX + BALL_RADIUS; x++) {
            float distance = std::sqrt(std::pow(x - ballCenterX, 2) + std::pow(y - ballCenterY, 2));
            if (distance <= BALL_RADIUS / 2) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

    // Draw debug info
    if (!isDebug) {
        SDL_RenderPresent(renderer);
        return;
    }

    // Draw raycasts
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < 2; i++) {
        int paddleY = i == 0 ? paddle1Y : paddle2Y;
        int paddleX = i == 0 ? 20 : WINDOW_WIDTH - PADDLE_WIDTH - 20;
        for (int j = 0; j < 4; j++) {
            int cornerX = paddleX + (j % 2 == 0 ? 0 : PADDLE_WIDTH);
            int cornerY = paddleY + (j < 2 ? 0 : PADDLE_HEIGHT);
            SDL_RenderDrawLine(renderer, ballCenterX, ballCenterY, cornerX, cornerY);
        }
    }

    // Draw ball trajectory line with bounce trajectory
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int predictX = ballX;
    int predictY = ballY;
    int predictVelocityX = ballVelocityX;
    int predictVelocityY = ballVelocityY;
    for (int i = 0; i < 100; i++) {
        predictX += predictVelocityX;
        predictY += predictVelocityY;

        // Check collision with paddles
        if (predictX <= PADDLE_WIDTH + 20 && predictY + BALL_RADIUS >= paddle1Y && predictY <= paddle1Y + PADDLE_HEIGHT) {
            predictX = PADDLE_WIDTH + 20;
            predictVelocityX = std::abs(predictVelocityX) * VELOCITY_INCREASE_FACTOR;
        } else if (predictX >= WINDOW_WIDTH - PADDLE_WIDTH - BALL_RADIUS - 20 && predictY + BALL_RADIUS >= paddle2Y && predictY <= paddle2Y + PADDLE_HEIGHT) {
            predictX = WINDOW_WIDTH - PADDLE_WIDTH - BALL_RADIUS - 20;
            predictVelocityX = -std::abs(predictVelocityX) * VELOCITY_INCREASE_FACTOR;
        }

        // Check collision with walls
        if (predictY <= 0 || predictY >= WINDOW_HEIGHT - BALL_RADIUS) {
            predictY = predictY <= 0 ? 0 : WINDOW_HEIGHT - BALL_RADIUS;
            predictVelocityY = -predictVelocityY;
        }
        SDL_RenderDrawPoint(renderer, predictX, predictY);
    }

    // Draw ball
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int predictCenterX = predictCenterX + BALL_RADIUS / 2;
    int predictCenterY = predictCenterY + BALL_RADIUS / 2;
    for (int y = predictY; y < predictY + BALL_RADIUS; y++) {
        for (int x = predictX; x < predictX + BALL_RADIUS; x++) {
            float distance = std::sqrt(std::pow(x - predictCenterX, 2) + std::pow(y - predictCenterY, 2));
            if (distance <= BALL_RADIUS / 2) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

int WinMain(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("MLR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    while (isRunning) {
        handleEvents();
        if (isPaused) continue;

        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if (keystates[SDL_SCANCODE_W]) {
            movePaddle1Up();
        }
        if (keystates[SDL_SCANCODE_S]) {
            movePaddle1Down();
        }
        if (keystates[SDL_SCANCODE_I]) {
            movePaddle2Up();
        }
        if (keystates[SDL_SCANCODE_K]) {
            movePaddle2Down();
        }

        update();
        render();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}