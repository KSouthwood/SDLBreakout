//
// Created by Keri Southwood-Smith on 6 March 2020.
//
#include "Controller.h"

//TODO: Use switch(event->type) structure instead of if's??
//      Shouldn't be a problem to nest switches
void Controller::EventHandler(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        running = false;
    }

    if (event->type == SDL_MOUSEMOTION) {
        Paddle::paddle.MouseMove(event->motion.x);
    }

    if (event->type == SDL_MOUSEBUTTONDOWN) {
        switch (event->button.button) {
        case SDL_BUTTON_LEFT:
            ball.LaunchBall(Ball::DIR_LEFT);
            break;
        case SDL_BUTTON_RIGHT:
            ball.LaunchBall(Ball::DIR_RIGHT);
        }
    }

    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
        case SDLK_LEFT:
            Paddle::paddle.KeyMove(-8);
            break;
        case SDLK_RIGHT:
            Paddle::paddle.KeyMove(8);
            break;
        case SDLK_q:
            running = false;
            break;
        case SDLK_SPACE:
            if (Paddle::paddle.getPosition().x < WINDOW_WIDTH / 2) {
                ball.LaunchBall(Ball::DIR_LEFT);
            } else {
                ball.LaunchBall(Ball::DIR_RIGHT);
            }
            break;
        default:
            break;
        }


    }
}