//
// Created by Jonas Luven on 01.04.23.
//



// brick.h
#pragma once
#include <SDL.h>
#include "bricks.h"

Brick::Brick(int x, int y, int width, int height, SDL_Renderer *renderer)
        : renderer(renderer) {
    brick = {x, y, width, height};
}

Brick::~Brick() {
}

void Brick::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &brick);
}

SDL_Rect *Brick::getRect() {
    return &brick;
}

