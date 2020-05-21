//
// Created by Keri Southwood-Smith on 10 January 2020.
//

#include "Controller.h"

Controller::Controller() : running(true) {
    FUNC_CALL(Controller());
}

void Controller::CleanUp() {
    FUNC_CALL(CleanUp());
    textureMap.Cleanup();
}

void Controller::Loop(SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer) {
    this->window = sdlWindow;
    this->renderer = sdlRenderer;

    LoadTextures();
    SDL_Event event;
    int title_timestamp = SDL_GetTicks();

    while (running) {

        while (SDL_PollEvent(&event)) {
            EventHandler(&event);
        }

        ball.Move(paddle, fpsControl);
        if (ball.outOfBounds) {
            if (--lives == 0) {
                running = false;
                break;
            } else {
                ball.onPaddle = true;
                ball.outOfBounds = false;
            }
        }

        for (auto & brick : bricks) {
//            if (AABBCollisionCheck(brick)) {
            if (CircleCollisionCheck(brick)) {
                BounceBall(brick);
                brick.setDestroyed(true);
            }
        }

        if (SDL_HasIntersection(&ball.getPosition(), &paddle.getPosition())) {
            PaddleCollision();
        }

        Render();
        fpsControl.onLoop();

        if (title_timestamp + 1000 <= SDL_GetTicks()) {
            title_timestamp = SDL_GetTicks();
            std::string title =
                "Breakout     FPS: " + std::to_string(fpsControl.getFPS()) + " Speed: " + std::to_string(fpsControl.getSpeed());
            SDL_SetWindowTitle(sdlWindow, title.c_str());
        }
    }
}

void Controller::Render() {
    SDL_Color background = {0x00, 0x00, 0xff, 0xFF};
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b,
                           background.a);
    SDL_RenderClear(renderer);

    ball.Render();
    for (auto brick : bricks) {
        brick.Render();
    }
    paddle.Render();
    SDL_RenderPresent(renderer);
}

void Controller::LoadTextures() {
    FUNC_CALL(LoadTextures());
    paddle.CreatePaddle(window, renderer);
    textureMap.AddTexture(renderer, "brick", "brick.bmp");
    ball.CreateBall(window, renderer);
    int width = textureMap.GetID("brick")->GetWidth();
    int height = textureMap.GetID("brick")->GetHeight();
    bricks = {};
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 8; ++col) {
            bricks.emplace_back(textureMap.GetID("brick"));
            bricks.back().SetPosition(col * width, 50 + (row * height));
        }
    }
}
