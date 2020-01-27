//
// Created by Keri Southwood-Smith on 15 January 2020.
//

#ifndef BREAKOUT_TEXTUREMAP_H
#define BREAKOUT_TEXTUREMAP_H

#include <SDL2/SDL.h>
#include <iostream>
#include <map>

#include "Texture.h"

class TextureMap {
  public:
    void AddTexture(SDL_Renderer *renderer, const std::string &name,
                    const std::string &filename);
    void Cleanup();
    Texture *GetID(const std::string &name);

  private:
    static std::map<std::string, Texture*> texmap;
};

#endif // BREAKOUT_TEXTUREMAP_H
