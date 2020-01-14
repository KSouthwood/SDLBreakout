//
// Created by Keri Southwood-Smith on 1/12/20.
//

#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include <iostream>
#include <SDL2/SDL.h>

class Ball {
public:
    Ball(SDL_Window *window, SDL_Renderer *renderer);
    virtual ~Ball();

    void Move();
     int getXPos() const;
     int getYPos() const;
     SDL_Texture *getTexture() const;

   private:
    SDL_Texture *texture{};

     int xPos;
     int yPos;
    int xDir;
    int yDir;
    int xMax;
    int yMax;

    enum DIRECTIONS {UP = -1, DOWN = 1, LEFT = -1, RIGHT = 1};

    void CreateSurface(SDL_Renderer *rend);
};

#endif // BREAKOUT_BALL_H
