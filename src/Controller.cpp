//
// Created by Keri Southwood-Smith on 10 January 2020.
//

#include "Controller.h"

Controller::Controller() : running(true) {
    SDL_Log("********** Controller() **********");
}

void Controller::cleanUp() { SDL_Log("********** cleanUp() **********"); }

void Controller::loop(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer) {
    SDL_Log("********** loop() **********");
    this->window   = sdlWindow;
    this->renderer = sdlRenderer;

    initGame();
    SDL_Event event;
    int title_timestamp = SDL_GetTicks();

    SDL_Log("********** start loop **********");
    while (running) {
        while (SDL_PollEvent(&event)) {
            eventHandler(&event);
        }

        ball.move(paddle, fpsControl);
        if (ball.outOfBounds) {
            if (--lives == 0) {
                running = false;
                break;
            } else {
                ball.onPaddle    = true;
                ball.outOfBounds = false;
            }
        }

        for (auto &brick : bricks) {
            //            if (collisionCheckAABB(brick)) {
            if (collisionCheckCircle(brick)) {
                bounceBall(brick);
                brick.setDestroyed(true);
            }
        }

        if (SDL_HasIntersection(&ball.getPosition(), &paddle.getPosition())) {
            paddleCollision();
        }

        render();
        fpsControl.onLoop();

        if (title_timestamp + 1000 <= SDL_GetTicks()) {
            title_timestamp = SDL_GetTicks();
            std::string title =
                "Breakout     FPS: " + std::to_string(fpsControl.getFPS()) +
                " Speed: " + std::to_string(fpsControl.getSpeed());
            SDL_SetWindowTitle(sdlWindow, title.c_str());
        }
    }
}

void Controller::render() {
    SDL_Color background = {0x00, 0x00, 0xff, 0xFF};
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b,
                           background.a);
    SDL_RenderClear(renderer);

    ball.render();
    for (auto &brick : bricks) {
        brick.render();
    }
    paddle.render();
    SDL_RenderPresent(renderer);
}

void Controller::initGame() {
    SDL_Log("********** initGame() **********");
    paddle.createPaddle(window, renderer);
    ball.createBall(window, renderer);
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 16; ++col) {
            Brick brick = Brick(renderer);
            bricks.emplace_back(brick);
            bricks.back().setPosition(col * brick.getBounds().w,
                                      50 + (row * brick.getBounds().h));
        }
    }
}
