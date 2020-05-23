//
// Created by Keri Southwood-Smith on 11 February 2020.
//

#include "Paddle.h"

Paddle::Paddle() { SDL_Log("********** Paddle() **********"); }

Paddle::~Paddle() { SDL_Log("********** ~Paddle() **********"); }

void Paddle::createPaddle(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer) {
    this->renderer = sdlRenderer;
    int width      = 0;
    int height     = 0;

    SDL_GetWindowSize(sdlWindow, &width, &height);
    position.x = (width / 2) - (position.w / 2);
    position.y = height - 30;
    xMax       = width - position.w;
}

void Paddle::mouseMove(Sint32 new_pos) {
    // subtract half the paddle size so the middle of the paddle tracks the
    // mouse
    new_pos -= position.w / 2;
    // validate new_pos to be between window edges
    new_pos    = new_pos < 0 ? 0 : new_pos;
    new_pos    = new_pos > xMax ? xMax : new_pos;
    position.x = new_pos;
}

void Paddle::keyMove(int move, FPS &fpsControl) {
    mouseMove(static_cast<float>(position.x) +
              (static_cast<float>(move) * fpsControl.getSpeed()));
}

void Paddle::render() {
    boxRGBA(renderer, position.x, position.y, position.x + position.w,
            position.y + position.h, COLOR.r, COLOR.g, COLOR.b, COLOR.a);
}

const SDL_Rect &Paddle::getPosition() { return position; }
