#include <SDL.h>

#include <cmath>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 100;
const int BALL_RADIUS = 10;
const int PADDLE_SPEED = 5;
const int BALL_BASE_SPEED = 3;
const float VELOCITY_INCREASE_FACTOR = 1.1f;

bool isRunning = true;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int paddle1Y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
int paddle2Y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
float ballX = WINDOW_WIDTH / 2;
float ballY = WINDOW_HEIGHT / 2;
float ballVelocityX = BALL_BASE_SPEED;
float ballVelocityY = BALL_BASE_SPEED;
int bounceCount = 0;

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE) {
                SDL_Delay(500);  // Pause for 500 milliseconds (0.5 seconds)
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
    ballX += ballVelocityX;
    ballY += ballVelocityY;

    // Check collision with paddles
    if (ballX <= PADDLE_WIDTH && ballY + BALL_RADIUS >= paddle1Y && ballY <= paddle1Y + PADDLE_HEIGHT) {
        ballVelocityX = std::abs(ballVelocityX) * VELOCITY_INCREASE_FACTOR;
        bounceCount++;
    } else if (ballX >= WINDOW_WIDTH - PADDLE_WIDTH - BALL_RADIUS && ballY + BALL_RADIUS >= paddle2Y && ballY <= paddle2Y + PADDLE_HEIGHT) {
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw paddles
    SDL_Rect paddle1Rect = {0, paddle1Y, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle1Rect);

    SDL_Rect paddle2Rect = {WINDOW_WIDTH - PADDLE_WIDTH, paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT};
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

    SDL_RenderPresent(renderer);
}

int WinMain(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("MLR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    while (isRunning) {
        handleEvents();
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

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
