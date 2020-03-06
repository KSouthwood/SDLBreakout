//
// Created by Keri Southwood-Smith on 12 January 2020.
//

#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include <SDL2/SDL.h>
#include <iostream>

#include "Texture.h"
#include "FPS.h"
#include "Paddle.h"

class Ball {
  public:
    static Ball ball;

    Ball(SDL_Window *window, Texture *texture);
    Ball();
    ~Ball();

    void Move();
    void Render();
    const SDL_Rect &getPosition() const;
    void FlipXDir();
    void FlipYDir();
    float getYDir() const;
    void LaunchBall(float dir);
    float getXDir() const;

    constexpr static const float DIR_UP = -1.0f;
    constexpr static const float DIR_DOWN = 1.0f;
    constexpr static const float DIR_LEFT = -1.0f;
    constexpr static const float DIR_RIGHT = 1.0f;

  private:
    Texture *texture{};

    SDL_Rect bound_box{};
    float xPos{};
    float yPos{};
    float xDir{};
    float yDir{};
    int xMax{};
    int yMax{};

    bool onPaddle {true};
};

#endif // BREAKOUT_BALL_H
