//
// Created by Keri Southwood-Smith on 12 January 2020.
//

#include "Ball.h"

Ball Ball::ball;

Ball::Ball() = default;

Ball::Ball(SDL_Window *window, Texture *texture)
    : texture(texture), bound_box({0, 0, 0, 0}), xMax(0), yMax(0) {
    SDL_GetWindowSize(window, &xMax, &yMax);
    int width = texture->GetWidth();
    int height = texture->GetHeight();
    xPos = static_cast<float>(xMax) / 2.0f;
    yPos = static_cast<float>(yMax) - 50.0f;
    xDir = DIR_UP;
    yDir = DIR_LEFT;
    xMax -= width;
    yMax -= height;
    bound_box = {static_cast<int>(xPos), static_cast<int>(yPos), width, height};
}

Ball::~Ball() = default;

void Ball::Move() {
    if (onPaddle) {
        SDL_Rect pos = Paddle::paddle.getPosition();
        xPos = static_cast<float>(pos.x + (pos.w / 2) - (bound_box.w / 2));
        yPos = static_cast<float>(pos.y - bound_box.h);
    } else {
        xPos += xDir * FPS::FPSControl.getSpeed();
        yPos += yDir * FPS::FPSControl.getSpeed();

        if (xPos <= 0.0f) {
            FlipXDir();
            xPos = 0.0f;
        }

        if (xPos >= static_cast<float>(xMax)) {
            FlipXDir();
            xPos = static_cast<float>(xMax);
        }

        if (yPos <= 0) {
            FlipYDir();
            yPos = 0;
        }

        if (yPos >= static_cast<float>(yMax)) {
            FlipYDir();
            yPos = static_cast<float>(yMax);
        }
    }

    bound_box.x = static_cast<int>(xPos);
    bound_box.y = static_cast<int>(yPos);
}

void Ball::Render() { texture->Render(bound_box); }
const SDL_Rect &Ball::getPosition() const { return bound_box; }

void Ball::FlipXDir() { xDir *= -1.0f; }
void Ball::FlipYDir() { yDir *= -1.0f; }

float Ball::getXDir() const { return xDir; }
float Ball::getYDir() const { return yDir; }

void Ball::LaunchBall(float dir) {
    onPaddle = false;
    xDir = dir;
}
