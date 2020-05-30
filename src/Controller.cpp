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

        if (!ball.move(paddle, fpsControl)) {
            if (--lives == 0) {
                running = false;
                break;
            } else {
                ball.reset();
            }
        }

        for (auto brick = bricks.begin(); brick != bricks.end(); ++brick) {
            if (collisionCheckCircle(*brick)) {
                brick->setDestroyed(true);
                bricks.erase(brick);
                if (bricks.empty()) {
                    ball.reset();
                    initBricks();
                }
                break;
            }
        }

        if (SDL_HasIntersection(&ball.getBounds(), &paddle.getPosition())) {
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
    SDL_Color background = {0x00, 0x00, 0x00, 0xFF};
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
    initBricks();
}

void Controller::initBricks() {
    SDL_Color colors[6] = {
        {0xfe, 0x27, 0x12, 0xff}, // red
        {0xc2, 0x14, 0x60, 0xff}, // red-purple
        {0x86, 0x01, 0xaf, 0xff}, // purple
        {0x44, 0x24, 0xd6, 0xff}, // blue-purple
        {0x02, 0x47, 0xfe, 0xff}, // blue
        {0x34, 0x7c, 0x98, 0xff}  // blue-green
    };

    int color = 0;
    int width = 60;
    int height = 30;

    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 16; ++col) {
            SDL_Color brick_color = colors[color];
            SDL_Rect brick_pos = {col * width, 50 + (row * height), width, height};
            bricks.emplace_back(Brick(renderer, brick_pos, brick_color, (6 - row)));
        }
        ++color;
    }

}