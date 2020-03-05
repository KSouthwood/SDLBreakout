//
// Created by Keri Southwood-Smith on 11 February 2020.
//

#ifndef BREAKOUT_PADDLE_H
#define BREAKOUT_PADDLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "FPS.h"

class Paddle {
  public:
    static Paddle paddle;

    Paddle();
    ~Paddle();

    void CreatePaddle(SDL_Window *window, SDL_Renderer *renderer);
    void Move(Sint32 new_pos);
    void KeyMove(int move);

    void Render();
    const SDL_Rect &getPosition() const;

  private:
    SDL_Renderer *rend = nullptr;

    SDL_Color COLOR = {0x99, 0x66, 0xff, 0xff};
    SDL_Rect position = {0, 0,75, 15};

    int xMax = 0;
};

#endif // BREAKOUT_PADDLE_H
