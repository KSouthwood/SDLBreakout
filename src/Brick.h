//
// Created by Keri Southwood-Smith on 26 January 2020.
//

#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H

#include "Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

class Brick {
  public:
    Brick(SDL_Renderer *sdlRenderer);
    Brick(SDL_Renderer *sdlRenderer, SDL_Rect a_position, SDL_Color a_color,
          int a_score);
    ~Brick();

    void render();
    SDL_Rect getBounds() const;
    SDL_Rect getEdges() const;
    bool isDestroyed() const;
    void setDestroyed(bool flag);
    int getScore() const;

  private:
    SDL_Rect bound_box    = {0, 0, 0, 0};
    SDL_Rect edges        = {0, 0, 0, 0};
    SDL_Color brick_color = {0x00, 0x00, 0x00, 0xff};

    SDL_Renderer *renderer = nullptr;
    bool destroyed         = false;
    int score = 0;
};

#endif // BREAKOUT_BRICK_H
