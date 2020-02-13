//
// Created by Keri Southwood-Smith on 11 February 2020.
//

#ifndef BREAKOUT_PADDLE_H
#define BREAKOUT_PADDLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

class Paddle {
  public:
    Paddle();
    Paddle(SDL_Window *window, SDL_Renderer *renderer);
    ~Paddle();

    void Move(Sint32 new_pos);
    void Render();
    const SDL_Rect &getPaddle() const;

  private:
    SDL_Renderer *rend;

    SDL_Color COLOR = {0x99, 0x66, 0xff, 0xff};
    SDL_Rect PADDLE = {0, 0,75, 15};

    int xMax = 0;
};

#endif // BREAKOUT_PADDLE_H
