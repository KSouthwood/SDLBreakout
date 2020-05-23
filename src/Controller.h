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
    Controller();

    void cleanUp();
    void loop(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer);

  private:
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
    bool collisionCheckAABB(const Brick &ccBrick);
    void bounceBall(Brick &bBrick);
    void initGame();
    void paddleCollision();
    int clamp(int value, int min, int max);
    bool collisionCheckCircle(const Brick &ccBrick);
};

#endif // BREAKOUT_CONTROLLER_H
