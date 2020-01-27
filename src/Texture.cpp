//
// Created by Keri Southwood-Smith on 15 January 2020.
//

#include "Texture.h"

bool Texture::LoadTexture(SDL_Renderer *rend, const std::string &file) {
    bool loaded = false;
    renderer = rend;

    if (renderer != nullptr) {
        SDL_Surface *surface = SDL_LoadBMP(file.c_str());
        if (surface != nullptr) {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture == nullptr) {
                std::cerr << "SDL_CreateTextureFromSurface error: "
                          << SDL_GetError() << std::endl;
            } else {
                name = file;
                width = surface->w;
                height = surface->h;
                loaded = true;
            }
            SDL_FreeSurface(surface);
        } else {
            std::cerr << "SDL_LoadBMP error: " << SDL_GetError() << std::endl;
        }
    } else {
        std::cerr << "NULL renderer passed in.\n";
    }

    return loaded;
}

void Texture::Render(SDL_Rect dest) {
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

void Texture::Render(int x, int y) {
    SDL_Rect dest = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
}

int Texture::GetWidth() { return width; }

int Texture::GetHeight() { return height; }
