//
// Created by Keri Southwood-Smith on 11 February 2020.
//

#include "Paddle.h"

Paddle::Paddle() = default;

Paddle::Paddle(SDL_Window *window, SDL_Renderer *renderer) : rend(renderer) {
    int win_wid = 0;
    int win_hgt = 0;

    SDL_GetWindowSize(window, &win_wid, &win_hgt);
    PADDLE.x = (win_wid / 2) - (PADDLE.w / 2);
    PADDLE.y = win_hgt - 50;
    xMax = win_wid - PADDLE.w;
}

Paddle::~Paddle() = default;

void Paddle::Move(Sint32 new_pos) {
    // validate new_pos to be between window edges
    new_pos = new_pos < 0 ? 0 : new_pos;
    new_pos = new_pos > xMax ? xMax : new_pos;
    PADDLE.x = new_pos;
}

void Paddle::KeyMove(int move) {
    Move(static_cast<float>(PADDLE.x) + (static_cast<float>(move) * FPS::FPSControl.getSpeed()));
}

void Paddle::Render() {
    boxRGBA(rend, PADDLE.x, PADDLE.y, PADDLE.x + PADDLE.w, PADDLE.y + PADDLE.h, COLOR.r, COLOR.g,
            COLOR.b, COLOR.a);
}
const SDL_Rect &Paddle::getPaddle() const { return PADDLE; }
