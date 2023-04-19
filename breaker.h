#ifndef ASTROIDS_BREAKER_H
#define ASTROIDS_BREAKER_H
#include <SDL.h>
#include <vector>


class Breaker {
public:
    enum class directions {
        left,
        right,
        neutral
    };
    Breaker(int size,int speed,SDL_Renderer * renderer);
    ~Breaker();
    void move(directions dir);
    void draw(SDL_Renderer * renderer);
    std::vector<int> getCords();
    int getDir();
    SDL_Rect getRect();

private:
    SDL_Renderer * renderer;
    directions dir;
    SDL_Rect player;
    int speed,size,dx,x;
    bool active;

    bool collidesWith(SDL_Rect &rect);
};


#endif //ASTROIDS_BREAKER_H
