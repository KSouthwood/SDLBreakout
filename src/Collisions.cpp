//
// Created by Keri Southwood-Smith on 05 February 2020.
//
#include "Controller.h"

bool Controller::CollisionCheck(const Brick& ccBrick) {
    if (ccBrick.isDestroyed()) {
        return false;
    }
    SDL_Rect ballPos = ball.getPosition();
    SDL_Rect brickPos = ccBrick.getEdges();

    int ballMin = ballPos.x;
    int ballMax = ballPos.x + ballPos.w - 1;
    int brickMin = brickPos.x;
    int brickMax = brickPos.w;

    ballMin = ballMin < brickMin ? brickMin : ballMin;
    ballMax = ballMax > brickMax ? brickMax : ballMax;

    if (ballMax <= ballMin) {
        return false;
    }

    ballMin = ballPos.y;
    ballMax = ballPos.y + ballPos.h - 1;
    brickMin = brickPos.y;
    brickMax = brickPos.h;

    ballMin = ballMin < brickMin ? brickMin : ballMin;
    ballMax = ballMax > brickMax ? brickMax : ballMax;

    return ballMax > ballMin;
}

void Controller::BounceBall(Brick &bBrick) {
    FUNC_CALL(BounceBall());
    SDL_Rect ballPos = ball.getPosition();
    SDL_Rect brickPos = bBrick.getEdges();

    int ballL = ballPos.x;
    int ballR = ballPos.x + ballPos.w;
    int ballT = ballPos.y;
    int ballB = ballPos.y + ballPos.h;
    std::cout << "Ball : " << ballL << " " << ballR << " " << ballT << " "
              << ballB << "\n";

    int brickL = brickPos.x;
    int brickR = brickPos.w;
    int brickT = brickPos.y;
    int brickB = brickPos.h;
    std::cout << "Brick: " << brickL << " " << brickR << " " << brickT << " "
              << brickB << "\n";

    if (ballB >= brickB) {
        ball.FlipYDir();
        std::cout << "ballB >= brickB, flipY" << std::endl;
    }
    if (ballT <= brickT) {
        ball.FlipYDir();
        std::cout << "ballT <= brickT, flipY" << std::endl;
    }
    if (ballL <= brickL) {
        ball.FlipXDir();
        std::cout << "ballL <= brickL, flipX" << std::endl;
    }
    if (ballR >= brickR) {
        ball.FlipXDir();
        std::cout << "ballR >= brickR, flipX" << std::endl;
    }
}