#ifndef ASTROIDS_BALL_H
#define ASTROIDS_BALL_H
#include <SDL.h>
#include "breaker.h"
#include "bricks.h"


class Ball {
public:
    Ball(int size,int speed,SDL_Renderer *renderer, Breaker * breaker);
    ~Ball();
    void move();
    void draw(SDL_Renderer * renderer);
    void reset(Breaker * breaker);
    void launch(Breaker *breaker);
    void changeDirection(const SDL_Rect &breakerRect);
    bool collidesWith(SDL_Rect rect);
    bool collidesWithB(Brick * bricks);
    void changeDirection();
private:
    int dx,dy,x,y,speed;
    bool active;
    SDL_Rect ball;
    Breaker * breaker;
    SDL_Renderer * renderer;

};


#endif //ASTROIDS_BALL_H
