//
// Created by Keri Southwood-Smith on 10 January 2020.
//

#ifndef BREAKOUT_CONTROLLER_H
#define BREAKOUT_CONTROLLER_H

#include <SDL2/SDL.h>
#include <list>

#include "Ball.h"
#include "Brick.h"
#include "FPS.h"
#include "Paddle.h"
#include "TextureMap.h"

class Controller {
  public:
    Controller(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer);

    static void cleanUp();
    void loop();

  private:
    int score    = 0;
    int lives    = 3;
    bool running = false;

    Ball ball = Ball();
    std::list<Brick> bricks {};
    Paddle paddle  = Paddle();
    FPS fpsControl = FPS();

    SDL_Window *window     = nullptr;
    SDL_Renderer *renderer = nullptr;

    void render();
    void eventHandler(SDL_Event *event);
    void initGame();
    void paddleCollision();
    static int clamp(float f_value, int min, int max);
    bool collisionCheckCircle(const Brick &a_brick);
    void initBricks();
};

#endif // BREAKOUT_CONTROLLER_H
