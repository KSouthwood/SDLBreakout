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
    //    ~Ball();

    bool move(Paddle &paddle, FPS &fpsControl);
    void render();
    void createBall(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer);
    void reset();
    void launchBall(float dir);
    void setXDir(float new_dir);
    void setYDir(float new_dir);

    const SDL_Rect &getBounds() const;
    SDL_FPoint &getPosition();
    float getRadius() const;
    float getYDir() const;
    float getXDir() const;

    constexpr static float DIR_UP    = -1.0f;
    constexpr static float DIR_DOWN  = 1.0f;
    constexpr static float DIR_LEFT  = -1.0f;
    constexpr static float DIR_RIGHT = 1.0f;

  private:
    float RADIUS = 10.0;

    SDL_Color COLOR        = {0xdd, 0xdd, 0xdd, 0xff};
    SDL_Renderer *renderer = nullptr;
    SDL_Rect bound_box     = {0, 0, static_cast<int>(RADIUS * 2),
                          static_cast<int>(RADIUS * 2)};
    SDL_FPoint position    = {0.0, 0.0};
    SDL_FPoint direction   = {DIR_LEFT, DIR_UP};

    float xMax    = 0;
    float yMax    = 0;
    bool onPaddle = true;
};

#endif // BREAKOUT_BALL_H
