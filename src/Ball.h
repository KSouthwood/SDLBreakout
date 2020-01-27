//
// Created by Keri Southwood-Smith on 12 January 2020.
//

#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include <SDL2/SDL.h>
#include <iostream>

#include "Texture.h"

class Ball {
  public:
    Ball(SDL_Window *window, Texture *texture);
    ~Ball();

    void Move();
    void Render();

  private:
    Texture *texture;
    SDL_Rect position;

    int xPos;
    int yPos;
    int xDir;
    int yDir;
    int xMax;
    int yMax;

    enum DIRECTIONS { UP = -1, DOWN = 1, LEFT = -1, RIGHT = 1 };
};

#endif // BREAKOUT_BALL_H
