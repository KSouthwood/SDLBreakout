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
//    Ball(SDL_Window *window, Texture *texture);
    Ball();
    ~Ball();

    void Move(Paddle &paddle, FPS &fpsControl);
    void Render();
    const SDL_Rect &getPosition() const;
    void FlipXDir();
    void FlipYDir();
    float getYDir() const;
    void LaunchBall(float dir);
    float getXDir() const;
    void CreateBall(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer);

    constexpr static float DIR_UP = -1.0f;
    constexpr static float DIR_DOWN = 1.0f;
    constexpr static float DIR_LEFT = -1.0f;
    constexpr static float DIR_RIGHT = 1.0f;

    bool outOfBounds = false;
    bool onPaddle = true;

  private:
    float RADIUS = 10.0;

    SDL_Color COLOR = {0xdd, 0xdd, 0xdd, 0xff};
    SDL_Renderer *renderer = nullptr;
    SDL_Rect bound_box = {0, 0, static_cast<int>(RADIUS * 2), static_cast<int>(RADIUS * 2)};
    SDL_FPoint position = {0.0, 0.0};

    float xMax = 0;
    float yMax = 0;

    float xDir = DIR_UP;
    float yDir = DIR_LEFT;
};

#endif // BREAKOUT_BALL_H
