//
// Created by Keri Southwood-Smith on 10 January 2020.
//

#ifndef BREAKOUT_CONTROLLER_H
#define BREAKOUT_CONTROLLER_H

#include <list>
#include <SDL2/SDL.h>

#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "TextureMap.h"
#include "FPS.h"

#define FUNC_CALL(func_name) std::cout << "********** " << #func_name << " **********\n"

class Controller {
  public:
    Controller();
    void CleanUp();
    void Loop(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer);

  private:
    int lives = 3;
    bool running;

    TextureMap textureMap;
    Ball ball = Ball();
    std::list<Brick> bricks;
    Paddle paddle = Paddle();

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    void Render();
    void EventHandler(SDL_Event *event);
    bool AABBCollisionCheck(const Brick& ccBrick);
    void BounceBall(Brick &bBrick);
    void LoadTextures();
    void PaddleCollision();
    int Clamp(int value, int min, int max);
    bool CircleCollisionCheck(const Brick &ccBrick);
};

#endif // BREAKOUT_CONTROLLER_H
