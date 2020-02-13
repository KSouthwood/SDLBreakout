//
// Created by Keri Southwood-Smith on 12 January 2020.
//

#include "Ball.h"

Ball::Ball() = default;

Ball::Ball(SDL_Window *window, Texture *texture)
    : texture(texture), bound_box({0, 0, 0, 0}), xMax(0), yMax(0) {
    SDL_GetWindowSize(window, &xMax, &yMax);
    int width = texture->GetWidth();
    int height = texture->GetHeight();
    xPos = xMax / 2;
    yPos = yMax - 50;
    xDir = UP;
    yDir = LEFT;
    xMax -= width;
    yMax -= height;
    bound_box = {xPos, yPos, width, height};
}

Ball::~Ball() = default;

void Ball::Move() {
    xPos += xDir;
    yPos += yDir;

    if (xPos <= 0) {
        xDir = RIGHT;
        xPos = 0;
    }

    if (xPos >= xMax) {
        xDir = LEFT;
        xPos = xMax;
    }

    if (yPos <= 0) {
        yDir = DOWN;
        yPos = 0;
    }

    if (yPos >= yMax) {
        yDir = UP;
        yPos = yMax;
    }

    bound_box.x = xPos;
    bound_box.y = yPos;
}

void Ball::Render() { texture->Render(bound_box); }
const SDL_Rect &Ball::getPosition() const { return bound_box; }

void Ball::FlipXDir() { Ball::xDir = Ball::xDir == RIGHT ? LEFT : RIGHT; }
void Ball::FlipYDir() { Ball::yDir = Ball::yDir == UP ? DOWN : UP; }

int Ball::getYPos() const { return yPos; }
int Ball::getYDir() const { return yDir; }
