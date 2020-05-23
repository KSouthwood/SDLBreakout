//
// Created by Keri Southwood-Smith on 26 January 2020.
//

#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Texture.h"

class Brick {
  public:
    Brick(SDL_Renderer *sdlRenderer);
    void SetPosition(int x, int y);
    void Render();
    SDL_Rect getBounds() const;
    SDL_Rect getEdges() const;
    bool isDestroyed() const;
    void setDestroyed(bool flag);
    virtual ~Brick();

  private:
    int xPos { 0 };
    int yPos { 0 };
    int width { 60 };
    int height { 30 };

    SDL_Rect bound_box { xPos, yPos, width, height };
    SDL_Rect edges { xPos, yPos, width, height };
    SDL_Color brick_color { 0x00, 0x00, 0x00, 0xff };

    SDL_Renderer *renderer { nullptr };
    bool destroyed { false };
};

#endif // BREAKOUT_BRICK_H
