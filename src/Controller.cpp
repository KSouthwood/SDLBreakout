//
// Created by Keri Southwood-Smith on 10 January 2020.
//

#include "Controller.h"

#define FUNC_CALL(func_name) std::cout << "********** " << #func_name << " **********\n"

Controller::Controller() : running(true) {
    FUNC_CALL(Controller());
}

bool Controller::OnInit() {
    FUNC_CALL(OnInit());
    bool success = false;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == 0) {
        window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
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
    FUNC_CALL(CleanUp());
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

    while (running) {
        while (SDL_PollEvent(&event)) {
            EventHandler(&event);
        }

        ball.Move();
        Render();
        for (auto brick = bricks.begin(); brick != bricks.end(); ++brick) {
            if (CollisionCheck(*brick)) {
                BounceBall(*brick);
                brick->setDestroyed(true);
            }
        }
    }
}

void Controller::Render() {
    FUNC_CALL(Render());
    SDL_Color background = {0x00, 0x00, 0xff, 0xFF};
    SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b,
                           background.a);
    SDL_RenderClear(renderer);

    ball.Render();
    for (auto brick : bricks) {
        brick.Render();
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(1000 / 240);
}

void Controller::EventHandler(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        running = false;
    }
}



void Controller::LoadTextures() {
    FUNC_CALL(LoadTextures());
    textureMap.AddTexture(renderer, "ball", "ball.bmp");
    textureMap.AddTexture(renderer, "brick", "brick.bmp");
    ball = Ball(window, textureMap.GetID("ball"));
    int width = textureMap.GetID("brick")->GetWidth();
    bricks = {};
    for (int i = 0; i < 5; ++i) {
        bricks.emplace_back(textureMap.GetID("brick"));
        bricks.back().SetPosition(10 + i * (width + 10), 50);
    }
}
