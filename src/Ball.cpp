//
// Created by Keri Southwood-Smith on 12 January 2020.
//

#include "Ball.h"

Ball::Ball() {
    std::cout << "********** Ball() **********\n";
}

Ball::~Ball() {
    std::cout << "********** ~Ball() **********\n";
}

void Ball::CreateBall(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer) {
    int win_x = 0;
    int win_y = 0;
    SDL_GetWindowSize(sdlWindow, &win_x, &win_y);
    this->renderer = sdlRenderer;
    position.x = static_cast<float>(win_x) / 2.0f;
    position.y = static_cast<float>(win_y) - 50.0f;
    xMax = static_cast<float>(win_x) - this->RADIUS;
    yMax = static_cast<float>(win_y) - this->RADIUS;
    bound_box.x = static_cast<int>(position.x);
    bound_box.y = static_cast<int>(position.y);
}

void Ball::Move(Paddle &paddle, FPS &fpsControl) {
    if (onPaddle) {
        SDL_Rect pos = paddle.getPosition();
        position.x = static_cast<float>(pos.x) + (static_cast<float>(pos.w) / 2.0f);
        position.y = static_cast<float>(pos.y) - RADIUS;
    } else {
        position.x += xDir * fpsControl.getSpeed();
        position.y += yDir * fpsControl.getSpeed();

        if (position.x <= RADIUS) {
            FlipXDir();
            position.x = RADIUS;
        }

        if (position.x >= xMax) {
            FlipXDir();
            position.x = xMax;
        }

        if (position.y <= RADIUS) {
            FlipYDir();
            position.y = RADIUS;
        }

        if (position.y >= yMax) {
            outOfBounds = true;
        }
    }

    bound_box.x = static_cast<int>(position.x - RADIUS);
    bound_box.y = static_cast<int>(position.y - RADIUS);
}

void Ball::Render() {
    filledCircleRGBA(renderer, position.x, position.y, (bound_box.h / 2),
                     COLOR.r, COLOR.g, COLOR.b, COLOR.a);
}

const SDL_Rect &Ball::getPosition() const { return bound_box; }

void Ball::FlipXDir() { xDir *= -1.0f; }
void Ball::FlipYDir() { yDir *= -1.0f; }

float Ball::getXDir() const { return xDir; }
float Ball::getYDir() const { return yDir; }

void Ball::LaunchBall(float dir) {
    if (onPaddle) {
        onPaddle = false;
        xDir     = dir;
    }
}