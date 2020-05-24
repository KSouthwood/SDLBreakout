//
// Created by Keri Southwood-Smith on 26 January 2020.
//

#include "Brick.h"

Brick::Brick(SDL_Renderer *sdlRenderer) : renderer(sdlRenderer) {
    SDL_Log("********** Brick() **********");
}

Brick::~Brick() { SDL_Log("********** ~Brick() **********"); }

Brick::Brick(SDL_Renderer *sdlRenderer, SDL_Rect a_position, SDL_Color a_color,
             int a_score)
    : bound_box(a_position), brick_color(a_color), renderer(sdlRenderer),
      score(a_score) {
    SDL_Log("********** Brick(pos, col, ren) **********");
    // use the .w & .h members to indicate the right and bottom edges so we
    // don't have to compute in the collision routines every time
    edges = {a_position.x, a_position.y, a_position.x + a_position.w,
             a_position.y + a_position.h};
}

void Brick::render() {
    if (!destroyed) {
        boxRGBA(renderer, edges.x, edges.y, edges.w, edges.h, brick_color.r,
                brick_color.g, brick_color.b, brick_color.a);
        rectangleRGBA(renderer, edges.x, edges.y, edges.w, edges.h, 0x00, 0x00,
                      0x00, 0xff);
    }
}

SDL_Rect Brick::getEdges() const { return edges; }

SDL_Rect Brick::getBounds() const { return bound_box; }

bool Brick::isDestroyed() const { return destroyed; }

void Brick::setDestroyed(bool flag) { destroyed = flag; }
