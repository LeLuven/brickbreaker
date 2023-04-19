#include "ball.h"
#include "breaker.h"
#include <iostream>

Ball::Ball(int size, int speed, SDL_Renderer *renderer, Breaker *breaker)
        : speed(speed), renderer(renderer), breaker(breaker) {
    active = false;
    x = 640 / 2 - size / 2;
    y = 600;
    dx = 0;
    dy = -1;
    ball = {x, y, size, size};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
}

Ball::~Ball() {

}

bool Ball::collidesWith(SDL_Rect rect) {
    return SDL_HasIntersection(&ball, &rect);
}
void Ball::changeDirection(const SDL_Rect &breakerRect) {
    // Calculate the relative collision position on the breaker
    float collisionPosition = static_cast<float>(ball.x + ball.w / 2 - breakerRect.x) / breakerRect.w;

    if (collisionPosition < 1.0f / 3.0f) {  // Left third
        dx = -1;
        dy = -1;
    } else if (collisionPosition > 2.0f / 3.0f) {  // Right third
        dx = 1;
        dy = -1;
    } else {  // Middle third
        dy = -1;
    }
}

void Ball::reset(Breaker *breaker) {
    active = false;
    std::vector<int> info = breaker->getCords();
    int b_x = info[0];
    int b_size = info[1];
    dx = 0;
    dy = -1;
    x = b_x + b_size / 2 - ball.w / 2;
    y = 620 - ball.h;
    ball.x = x;
    ball.y = y;
}


void Ball::move() {
    if (active) {
        x += speed * dx;
        y += speed * dy;
        if (x < 0) {
            dx = -dx;
        }
        if (x + ball.w >= 640) {
            dx = -dx;
        }
        if (y < 0) {
            dy = -dy;
        }
        if (y + ball.h >= 640) {
            dy = -dy;
            reset(breaker);
        }
        ball.x = x;
        ball.y = y;
    }
    else {
        reset(breaker);
    }
}

void Ball::launch(Breaker *breaker) {
    if(!active) {
        dx = breaker->getDir();
        //std::cout << ball.
        active = true;
    }
}
bool Ball::collidesWithB(Brick * brick) {
    return SDL_HasIntersection(&ball, brick->getRect());
}


void Ball::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &ball);
}

void Ball::changeDirection() {
    dy = -dy;
}
