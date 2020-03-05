//
// Created by Keri Southwood-Smith on 11 February 2020.
//

#include "Paddle.h"

Paddle Paddle::paddle;

Paddle::Paddle() = default;

Paddle::~Paddle() = default;

void Paddle::CreatePaddle(SDL_Window *window, SDL_Renderer *renderer) {
    rend = renderer;
    int win_wid = 0;
    int win_hgt = 0;

    SDL_GetWindowSize(window, &win_wid, &win_hgt);
    position.x = (win_wid / 2) - (position.w / 2);
    position.y = win_hgt - 30;
    xMax = win_wid - position.w;
}

void Paddle::Move(Sint32 new_pos) {
    // validate new_pos to be between window edges
    new_pos = new_pos < 0 ? 0 : new_pos;
    new_pos = new_pos > xMax ? xMax : new_pos;
    position.x = new_pos;
}

void Paddle::KeyMove(int move) {
    Move(static_cast<float>(position.x) + (static_cast<float>(move) * FPS::FPSControl.getSpeed()));
}
void Paddle::Render() {
    boxRGBA(rend, position.x, position.y, position.x + position.w,
            position.y + position.h, COLOR.r, COLOR.g,
            COLOR.b, COLOR.a);
}
const SDL_Rect &Paddle::getPosition() const { return position; }
