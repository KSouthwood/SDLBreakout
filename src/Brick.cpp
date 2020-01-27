//
// Created by Keri Southwood-Smith on 26 January 2020.
//

#include "Brick.h"

Brick::Brick(Texture *texture) : texture(texture), xPos(0), yPos(0) {}

void Brick::SetPosition(int x, int y) {
    xPos = x;
    yPos = y;
    position = {xPos, yPos, texture->GetWidth(), texture->GetHeight()};
}

void Brick::Render() { texture->Render(position); }
