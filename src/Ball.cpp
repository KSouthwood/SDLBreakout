//
// Created by Keri Southwood-Smith on 12 January 2020.
//

#include "Ball.h"

Ball::Ball() { SDL_Log("********** Ball() **********"); }

Ball::~Ball() { SDL_Log("********** ~Ball() **********"); }

void Ball::createBall(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer) {
    SDL_Log("********** createBall() **********");
    int win_x = 0;
    int win_y = 0;
    SDL_GetWindowSize(sdlWindow, &win_x, &win_y);
    this->renderer = sdlRenderer;
    position.x     = static_cast<float>(win_x) / 2.0f;
    position.y     = static_cast<float>(win_y) - 50.0f;
    xMax           = static_cast<float>(win_x) - this->RADIUS;
    yMax           = static_cast<float>(win_y) - this->RADIUS;
    bound_box.x    = static_cast<int>(position.x);
    bound_box.y    = static_cast<int>(position.y);
}

void Ball::reset() {
    SDL_Log("********** ball.reset() **********");
    onPaddle = true;
}

/*
 * Move the ball checking for rebounds off the sides of the window.
 * Returns false if we reach the bottom indicating the player missed it.
 */
bool Ball::move(Paddle &paddle, FPS &fpsControl) {
    bool success = true;
    if (onPaddle) {
        SDL_Rect pos = paddle.getPosition();
        position.x =
            static_cast<float>(pos.x) + (static_cast<float>(pos.w) / 2.0f);
        position.y = static_cast<float>(pos.y) - RADIUS;
    } else {
        position.x += direction.x * fpsControl.getSpeed();
        position.y += direction.y * fpsControl.getSpeed();

        if (position.x <= RADIUS) {
            flipXDir();
            position.x = RADIUS;
        }

        if (position.x >= xMax) {
            flipXDir();
            position.x = xMax;
        }

        if (position.y <= RADIUS) {
            flipYDir();
            position.y = RADIUS;
        }

        if (position.y >= yMax) {
            success = false;
        }
    }

    bound_box.x = static_cast<int>(position.x - RADIUS);
    bound_box.y = static_cast<int>(position.y - RADIUS);

    return success;
}

void Ball::render() {
    filledCircleRGBA(renderer, position.x, position.y, (bound_box.h / 2),
                     COLOR.r, COLOR.g, COLOR.b, COLOR.a);
}

// Get the center position of the ball
SDL_FPoint &Ball::getPosition() { return position; }

// Get the bounding box of the ball
const SDL_Rect &Ball::getBounds() const { return bound_box; }

void Ball::flipXDir() { direction.x *= -1.0f; }
void Ball::flipYDir() { direction.y *= -1.0f; }

float Ball::getXDir() const { return direction.x; }
float Ball::getYDir() const { return direction.y; }

void Ball::launchBall(float dir) {
    if (onPaddle) {
        onPaddle    = false;
        direction.x = dir;
    }
}
float Ball::getRadius() { return RADIUS; }
