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

#define FUNC_CALL(func_name) std::cout << "********** " << #func_name << " **********\n"

class Controller {
  public:
    Controller();
    bool OnInit();
    void CleanUp();
    void Loop();

  private:
    int WINDOW_WIDTH = 480;
    int WINDOW_HEIGHT = 640;

    bool running;

    TextureMap textureMap;
    Ball ball;
    std::list<Brick> bricks;
    Paddle paddle;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    void Render();
    void EventHandler(SDL_Event *event);
    bool CollisionCheck(const Brick& ccBrick);
    void BounceBall(Brick &bBrick);
    void LoadTextures();
};

#endif // BREAKOUT_CONTROLLER_H
