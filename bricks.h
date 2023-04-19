#ifndef ASTROIDS_BRICKS_H
#define ASTROIDS_BRICKS_H
#include <SDL.h>
#include <vector>

#pragma once
#include <SDL.h>

class Brick {
public:
    Brick(int x, int y, int width, int height, SDL_Renderer *renderer);
    ~Brick();

    void draw(SDL_Renderer *renderer);
    SDL_Rect *getRect();

private:
    SDL_Rect brick;
    SDL_Renderer *renderer;
};


#endif //ASTROIDS_BRICKS_H
