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
    SDL_Rect bound_box{};
    SDL_Rect edges{};

    Texture *texture;
    bool destroyed;

  public:
    Brick(Texture *texture);
    void SetPosition(int x, int y);
    void Render();
    const SDL_Rect &getBounds();
    SDL_Rect getEdges() const;
    bool isDestroyed() const;
    void setDestroyed(bool flag);
    virtual ~Brick();
};

#endif // BREAKOUT_BRICK_H
