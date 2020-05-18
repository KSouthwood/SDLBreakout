//
// Created by Keri Southwood-Smith on 26 January 2020.
//

#include "Brick.h"

Brick::Brick(Texture *texture)
    : texture(texture), xPos(0), yPos(0), destroyed(false) {}

Brick::~Brick() {}

void Brick::SetPosition(int x, int y) {
    xPos = x;
    yPos = y;
    bound_box = {xPos, yPos, texture->GetWidth(), texture->GetHeight()};
    // use the .w & .h members to indicate the right and bottom edges so we
    // don't have to compute in the collision routines every time
    edges = {xPos, yPos, xPos + texture->GetWidth(),
             yPos + texture->GetHeight()};
}

void Brick::Render() {
    if (!destroyed) {
        texture->Render(bound_box);
    }
}

SDL_Rect Brick::getEdges() const { return edges; }

SDL_Rect Brick::getBounds() const { return bound_box; }

bool Brick::isDestroyed() const { return destroyed; }

void Brick::setDestroyed(bool flag) {
    destroyed = flag;
}
