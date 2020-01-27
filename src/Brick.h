//
// Created by Keri Southwood-Smith on 26 January 2020.
//

#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H

#include "Texture.h"

class Brick {
  private:
    int xPos{};
    int yPos{};
    SDL_Rect position{};

    Texture *texture;

  public:
    Brick(Texture *texture);
    void SetPosition(int x, int y);
    void Render();
};

#endif // BREAKOUT_BRICK_H
