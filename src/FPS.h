//
// Created by Keri Southwood-Smith on 21 February 2020.
//

#ifndef BREAKOUT_FPS_H
#define BREAKOUT_FPS_H

#include <SDL2/SDL.h>

class FPS {
  public:
    static FPS FPSControl;

    FPS();
    void onLoop();
    float getSpeed();
    int getFPS();

  private:
    unsigned int FPS_MAX = 120;
    unsigned int MS_SECOND = 1000;
    float SPEED_FACTOR = 175.0;

    int timestamp;
    int frame_end;
    int frame_rate;
    int frames;
    float speed;
};

#endif // BREAKOUT_FPS_H
