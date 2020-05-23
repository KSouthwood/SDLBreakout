//
// Created by Keri Southwood-Smith on 21 February 2020.
//

#include "FPS.h"

FPS::FPS() { SDL_Log("********** FPS() **********"); }

FPS::~FPS() { SDL_Log("********** ~FPS() **********"); }

void FPS::onLoop() {
    if (timestamp + MS_SECOND < SDL_GetTicks()) {
        timestamp  = SDL_GetTicks();
        frame_rate = frames;
        frames     = 0;
    }

    speed = (static_cast<float>(SDL_GetTicks() - frame_end) /
             static_cast<float>(MS_SECOND)) *
            SPEED_FACTOR;
    frame_end = SDL_GetTicks();
    ++frames;

    if (FPS_MAX) {
        if ((SDL_GetTicks() - frame_end) < (MS_SECOND / FPS_MAX)) {
            SDL_Delay((MS_SECOND / FPS_MAX) - (SDL_GetTicks() - frame_end));
        }
    }
}

float FPS::getSpeed() const { return speed; }

int FPS::getFPS() const { return frame_rate; }
