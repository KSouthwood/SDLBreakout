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
    xPos = (float)xMax / 2.0f;
    yPos = (float)yMax - 50.0f;
    xDir = UP;
    yDir = LEFT;
    xMax -= width;
    yMax -= height;
    bound_box = {(int)xPos, (int)yPos, width, height};
}

Ball::~Ball() = default;

void Ball::Move() {
    xPos += (float)xDir * FPS::FPSControl.getSpeed();
    yPos += (float)yDir * FPS::FPSControl.getSpeed();

    if (xPos <= 0.0f) {
        xDir = RIGHT;
        xPos = 0.0f;
    }

    if (xPos >= (float)xMax) {
        xDir = LEFT;
        xPos = (float)xMax;
    }

    if (yPos <= 0) {
        yDir = DOWN;
        yPos = 0;
    }

    if (yPos >= (float)yMax) {
        yDir = UP;
        yPos = (float)yMax;
    }

    bound_box.x = (int)xPos;
    bound_box.y = (int)yPos;
}

void Ball::Render() { texture->Render(bound_box); }
const SDL_Rect &Ball::getPosition() const { return bound_box; }

void Ball::FlipXDir() { Ball::xDir = Ball::xDir == RIGHT ? LEFT : RIGHT; }
void Ball::FlipYDir() { Ball::yDir = Ball::yDir == UP ? DOWN : UP; }

int Ball::getYPos() const { return (int)yPos; }
int Ball::getYDir() const { return yDir; }
