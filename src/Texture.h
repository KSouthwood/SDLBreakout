//
// Created by keri on 1/15/20.
//

#ifndef BREAKOUT_TEXTURE_H
#define BREAKOUT_TEXTURE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>

class Texture {
  private:
    std::string name = "";

  protected:
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *texture = nullptr;
    int width = 0;
    int height = 0;

  public:
    bool LoadTexture(SDL_Renderer *rend, const std::string &file);
    void Render(SDL_Rect dest);
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
};

#endif // BREAKOUT_TEXTURE_H
