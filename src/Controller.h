//
// Created by Keri Southwood-Smith on 10 January 2020.
//

#ifndef BREAKOUT_CONTROLLER_H
#define BREAKOUT_CONTROLLER_H

#include <SDL2/SDL.h>

#include "Ball.h"
#include "Brick.h"
#include "TextureMap.h"

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

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    void Render(Ball &ball, Brick &brick);
    void EventHandler(SDL_Event *event);
};

#endif // BREAKOUT_CONTROLLER_H
