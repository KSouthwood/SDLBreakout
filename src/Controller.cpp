//
// Created by Keri Southwood-Smith on 10 January 2020.
//

#include "Controller.h"

Controller::Controller() : running(true) {
    FUNC_CALL('Controller()');
}

bool Controller::OnInit() {
    FUNC_CALL('OnInit()');
    bool success = false;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == 0) {
        window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, // NOLINT(hicpp-signed-bitwise)
                                  SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, // NOLINT(hicpp-signed-bitwise)
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

        if (window != nullptr) {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (renderer != nullptr) {
                success = true;
            }
        }
    }

    return success;
}

void Controller::CleanUp() {
    FUNC_CALL('CleanUp()');
    textureMap.Cleanup();

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}

void Controller::Loop() {
    LoadTextures();
    SDL_Event event;
    int title_timestamp = SDL_GetTicks();

    while (running) {

        while (SDL_PollEvent(&event)) {
            EventHandler(&event);
        }

        ball.Move();
        for (auto & brick : bricks) {
            if (CollisionCheck(brick)) {
                BounceBall(brick);
                brick.setDestroyed(true);
            }
        }

        if (SDL_HasIntersection(&ball.getPosition(), &Paddle::paddle.getPosition())) {
            if (ball.getYPos() <
                Paddle::paddle.getPosition().y - ball.getPosition().h + 3) {
                if (ball.getYDir() == 1) {
                    ball.FlipYDir();
                }
            }
        }

        Render();
        FPS::FPSControl.onLoop();

        if (title_timestamp + 1000 < SDL_GetTicks()) {
            std::string title =
                "Breakout     FPS: " + std::to_string(FPS::FPSControl.getFPS()) + " Speed: " + std::to_string(FPS::FPSControl.getSpeed());
            SDL_SetWindowTitle(window, title.c_str());
            title_timestamp = SDL_GetTicks();
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
    Paddle::paddle.Render();
    SDL_RenderPresent(renderer);
}

//TODO: Use switch(event->type) structure instead of if's??
//      Shouldn't be a problem to nest switches
void Controller::EventHandler(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        running = false;
    }

    if (event->type == SDL_MOUSEMOTION) {
        Paddle::paddle.Move(event->motion.x);
    }

    if (event->type == SDL_MOUSEBUTTONDOWN) {
        ball.LaunchBall();
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
            ball.LaunchBall();
            break;
        default:
            break;
        }


    }
}

void Controller::LoadTextures() {
    FUNC_CALL('LoadTextures()');
    Paddle::paddle.CreatePaddle(window, renderer);
    textureMap.AddTexture(renderer, "ball", "ball.bmp");
    textureMap.AddTexture(renderer, "brick", "brick.bmp");
    ball = Ball(window, textureMap.GetID("ball"));
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
