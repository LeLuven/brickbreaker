#include "breaker.h"
#include <SDL.h>
#include <vector>

Breaker::Breaker(int size, int speed, SDL_Renderer *renderer)
        : size(size), speed(speed), renderer(renderer) {
    active = false;
    x = 640 / 2 - size / 2;
    player = {x, 620, size, 20};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


void Breaker::move(Breaker::directions dir) {
    switch (dir) {
        case directions::left:
            dx = -1;
            Breaker::dir = dir;
            break;
        case directions::right:
            Breaker::dir = dir;
            dx = 1;
            break;
        case directions::neutral:
            Breaker::dir = dir;
            dx = 0;
            break;

    }
    x += speed * dx;
    if (x < 0) {
        x = 0;
    } else if (x + size >= 640) {
        x = 640 - size;
    }

    player.x = x;
}
SDL_Rect Breaker::getRect() {
    return player;
}

bool Breaker::collidesWith(SDL_Rect &rect) {
    return SDL_HasIntersection(&player, &rect);
}


void Breaker::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,&player);

}

std::vector<int> Breaker::getCords() {
    std::vector<int> info;
    info.push_back(player.x);
    info.push_back(size);
    return info;
}

int Breaker::getDir() {
    return Breaker::dir == directions::left ? -1 : Breaker::dir == directions::right ? 1 : 0;
}

Breaker::~Breaker() = default;