//
// Created by Keri Southwood-Smith on 12 January 2020.
//

#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include <SDL2/SDL.h>

#include "FPS.h"
#include "Paddle.h"
#include "Texture.h"

class Ball {
  public:
    Ball();
    ~Ball();

    void move(Paddle &paddle, FPS &fpsControl);
    void render();
    const SDL_Rect &getBounds() const;
    SDL_FPoint &getPosition();
    void flipXDir();
    void flipYDir();
    float getYDir() const;
    void launchBall(float dir);
    float getXDir() const;
    void createBall(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer);

    constexpr static float DIR_UP    = -1.0f;
    constexpr static float DIR_DOWN  = 1.0f;
    constexpr static float DIR_LEFT  = -1.0f;
    constexpr static float DIR_RIGHT = 1.0f;

    bool outOfBounds = false;
    bool onPaddle    = true;

  private:
    float RADIUS = 10.0;

    SDL_Color COLOR        = {0xdd, 0xdd, 0xdd, 0xff};
    SDL_Renderer *renderer = nullptr;
    SDL_Rect bound_box     = {0, 0, static_cast<int>(RADIUS * 2),
                          static_cast<int>(RADIUS * 2)};
    SDL_FPoint position    = {0.0, 0.0};

    float xMax = 0;
    float yMax = 0;

    float xDir = DIR_UP;
    float yDir = DIR_LEFT;
};

#endif // BREAKOUT_BALL_H
