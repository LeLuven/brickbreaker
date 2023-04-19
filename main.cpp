#include <iostream>
#include <SDL.h>
#include "breaker.h"
#include "ball.h"
#include "bricks.h"

using namespace std;

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("My Window", 100, 100, 640, 640, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    SDL_Event event;
    Breaker breaker(150, 15, renderer);
    Ball ball(20, 10, renderer, &breaker);
    std::vector<std::unique_ptr<Brick>> bricks;


    int screenWidth = 640;
    int numRows = 4;
    int numBricksPerRow = 8;
    int brickWidth = 70;
    int brickHeight = 20;
    int brickSpacing = 10;

// Calculate the total width of all bricks and the spacing between them
    int totalBricksWidth = numBricksPerRow * brickWidth + (numBricksPerRow - 1) * brickSpacing;

// Calculate the left offset to make the bricks centered on the screen
    int leftOffset = (screenWidth - totalBricksWidth) / 2;

// Create bricks and add them to the bricks vector
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numBricksPerRow; ++j) {
            bricks.emplace_back(std::make_unique<Brick>(leftOffset + j * (brickWidth + brickSpacing),
                                                        50 + i * (brickHeight + brickSpacing), brickWidth, brickHeight,
                                                        renderer));
        }
    }


    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goto clean;
            }
        }

        SDL_PumpEvents();
        const Uint8 *keyboardState = SDL_GetKeyboardState(nullptr);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (keyboardState[SDL_SCANCODE_A] | keyboardState[SDL_SCANCODE_LEFT]) {
            breaker.move(Breaker::directions::left);
        } else if (keyboardState[SDL_SCANCODE_D] | keyboardState[SDL_SCANCODE_RIGHT]) {
            breaker.move(Breaker::directions::right);
        } else {
            breaker.move(Breaker::directions::neutral);
        }
        if (keyboardState[SDL_SCANCODE_SPACE]) {
            ball.launch(&breaker);
        }
        for (auto &brick: bricks) {
            brick->draw(renderer);
        }
        if (ball.collidesWith(breaker.getRect())) {
            ball.changeDirection(breaker.getRect());
        }
        for (size_t i = 0; i < bricks.size(); ) {
            if (ball.collidesWithB(bricks[i].get())) {
                bricks.erase(bricks.begin() + i);
                ball.changeDirection();
            } else {
                ++i;
            }
        }



            ball.move();
        ball.draw(renderer);
        breaker.draw(renderer);


        SDL_RenderPresent(renderer);


    }
    clean:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

