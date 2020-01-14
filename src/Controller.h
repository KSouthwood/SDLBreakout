//
// Created by Keri Southwood-Smith on 1/10/20.
//

#ifndef BREAKOUT_CONTROLLER_H
#define BREAKOUT_CONTROLLER_H

#include <SDL2/SDL.h>

#include "Ball.h"

class Controller {
  public:
    bool OnInit();
    void CleanUp();
    void Loop();

  private:
    unsigned int WINDOW_WIDTH  = 480;
    unsigned int WINDOW_HEIGHT = 640;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    void Render(Ball ball);
};

#endif // BREAKOUT_CONTROLLER_H
