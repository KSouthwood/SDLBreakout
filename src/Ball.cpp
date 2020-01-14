//
// Created by Keri Southwood-Smith on 1/12/20.
//

#include "Ball.h"

Ball::Ball(SDL_Window *window, SDL_Renderer *renderer) {
    xPos = 0;
    yPos = 0;
    xDir = DOWN;
    yDir = RIGHT;
    SDL_GetWindowSize(window, &xMax, &yMax);
    CreateSurface(renderer);
}

Ball::~Ball() {
//    SDL_DestroyTexture(texture);
}

void Ball::CreateSurface(SDL_Renderer* rend) {
    SDL_Surface* surface = SDL_LoadBMP("ball.bmp");
    if (surface != nullptr) {
        texture = SDL_CreateTextureFromSurface(rend, surface);
        if (texture == nullptr) {
            std::cout << "Couldn't create texture: " << SDL_GetError() << std::endl;
        } else {
            xMax -= surface->w;
            yMax -= surface->h;
        }
        SDL_FreeSurface(surface);
    } else {
        std::cout << "SDL_LoadBMP() error: " << SDL_GetError() << std::endl;
    }
}
void Ball::Move() {
    xPos += xDir;
    yPos += yDir;

    if (xPos <= 0) {
        xDir = (xDir == LEFT ? RIGHT : LEFT);
        xPos = 0;
    }

    if (xPos >= xMax) {
        xDir = (xDir == LEFT ? RIGHT : LEFT);
        xPos = xMax;
    }

    if (yPos <= 0) {
        yDir = (yDir == DOWN ? UP : DOWN);
        yPos = 0;
    }

    if (yPos >= yMax) {
        yDir = (yDir == DOWN ? UP : DOWN);
        yPos = yMax;
    }
}

 int Ball::getXPos() const { return xPos; }

int Ball::getYPos() const { return yPos; }
SDL_Texture *Ball::getTexture() const { return texture; }
