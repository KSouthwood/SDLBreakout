//
// Created by Keri Southwood-Smith on 12 January 2020.
//

#include "Ball.h"

Ball::Ball(SDL_Window *window, Texture *texture)
    : texture(texture), position({0, 0, 0, 0}), xMax(0), yMax(0) {
    SDL_GetWindowSize(window, &xMax, &yMax);
    int width = texture->GetWidth();
    int height = texture->GetHeight();
    xPos = xMax / 2;
    yPos = yMax - 50;
    xDir = UP;
    yDir = LEFT;
    xMax -= width;
    yMax -= height;
    position = {xPos, yPos, width, height};
}

Ball::~Ball() {}

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

    position.x = xPos;
    position.y = yPos;
}

void Ball::Render() { texture->Render(position); }
const SDL_Rect &Ball::getPosition() const { return bound_box; }

void Ball::FlipXDir() { Ball::xDir = Ball::xDir == RIGHT ? LEFT : RIGHT; }
void Ball::FlipYDir() { Ball::yDir = Ball::yDir == UP ? DOWN : UP; }

int Ball::getXPos() const { return xPos; }
int Ball::getYPos() const { return yPos; }
