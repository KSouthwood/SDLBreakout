//
// Created by Keri Southwood-Smith on 21 February 2020.
//

#include "FPS.h"
FPS FPS::FPSControl;

FPS::FPS() {
    timestamp = 0;
    frame_end = 0;
    frame_rate = 0;
    frames = 0;
    speed = 0.0f;
}

void FPS::onLoop() {
    if (timestamp + MS_SECOND < SDL_GetTicks()) {
        timestamp = SDL_GetTicks();
        frame_rate = frames;
        frames = 0;
    }

    speed = (static_cast<float>(SDL_GetTicks() - frame_end) / static_cast<float>(MS_SECOND)) * SPEED_FACTOR;
    frame_end = SDL_GetTicks();
    ++frames;

    if ((SDL_GetTicks() - frame_end) < (MS_SECOND / FPS_MAX)) {
        SDL_Delay((MS_SECOND / FPS_MAX) - (SDL_GetTicks() - frame_end));
    }
}

float FPS::getSpeed() { return speed; }

int FPS::getFPS() { return frame_rate; }
