//
// Created by Keri Southwood-Smith on 11 February 2020.
//

#ifndef BREAKOUT_PADDLE_H
#define BREAKOUT_PADDLE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "FPS.h"

class Paddle {
  public:
    Paddle();
    ~Paddle();

    void CreatePaddle(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer);
    void MouseMove(Sint32 new_pos);
    void KeyMove(int move, FPS fpsControl);

    void Render();
    const SDL_Rect &getPosition();

  private:
    int WIDTH = 75;
    int HEIGHT = 15;
    SDL_Renderer *renderer = nullptr;

    SDL_Color COLOR = {0x99, 0x66, 0xff, 0xff};
    SDL_Rect position = {0, 0,WIDTH, HEIGHT};

    int xMax = 0;
};

#endif // BREAKOUT_PADDLE_H
