//
// Created by Keri Southwood-Smith on 6 March 2020.
//
#include "Controller.h"

// TODO: Use switch(event->type) structure instead of if's??
//      Shouldn't be a problem to nest switches
void Controller::eventHandler(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        running = false;
    }

    if (event->type == SDL_MOUSEMOTION) {
        paddle.mouseMove(event->motion.x);
    }

    if (event->type == SDL_MOUSEBUTTONDOWN) {
        switch (event->button.button) {
        case SDL_BUTTON_LEFT:
            ball.launchBall(Ball::DIR_LEFT);
            break;
        case SDL_BUTTON_RIGHT:
            ball.launchBall(Ball::DIR_RIGHT);
            break;
        default:
            break;
        }
    }

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_LEFT:
            paddle.keyMove(-8, fpsControl);
            break;
        case SDLK_RIGHT:
            paddle.keyMove(8, fpsControl);
            break;
        case SDLK_q:
            running = false;
            break;
        case SDLK_SPACE:
            int width;
            SDL_GetWindowSize(window, &width, nullptr);
            if (paddle.getPosition().x < (width / 2)) {
                ball.launchBall(Ball::DIR_LEFT);
            } else {
                ball.launchBall(Ball::DIR_RIGHT);
            }
            break;
        default:
            break;
        }
    }
}