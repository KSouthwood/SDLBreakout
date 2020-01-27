//
// Created by Keri Southwood-Smith on 15 January 2020.
//

#include "TextureMap.h"

std::map<std::string, Texture*> TextureMap::texmap;

void TextureMap::AddTexture(SDL_Renderer *renderer, const std::string &name,
                            const std::string &filename) {
    if (!name.empty()) {
        auto *new_tex = new Texture();
        if (new_tex->LoadTexture(renderer, filename)) {
            texmap[name] = new_tex;
        } else {
            std::cerr << "Couldn't load texture: " << filename << std::endl;
        }
    }
}

void TextureMap::Cleanup() {
    if (!texmap.empty()) {
        for (auto &tex : texmap) {
            auto *texture = (Texture *)tex.second;

            if (texture) {
                delete texture;
                texture = nullptr;
            }
        }
    }

    texmap.clear();
}

Texture *TextureMap::GetID(const std::string &name) {
    return (texmap.find(name) == texmap.end()) ? nullptr : texmap[name];
}
