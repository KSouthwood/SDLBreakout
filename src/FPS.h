//
// Created by Keri Southwood-Smith on 21 February 2020.
//

#ifndef BREAKOUT_FPS_H
#define BREAKOUT_FPS_H

#include <SDL2/SDL.h>

class FPS {
  public:
    FPS();
    ~FPS();

    void onLoop();
    float getSpeed() const;
    int getFPS() const;

  private:
    unsigned int FPS_MAX   = 120;
    unsigned int MS_SECOND = 1000;
    float SPEED_FACTOR     = 175.0;

    int timestamp  = 0;
    int frame_end  = 0;
    int frame_rate = 0;
    int frames     = 0;
    float speed    = 0.0;
};

#endif // BREAKOUT_FPS_H
