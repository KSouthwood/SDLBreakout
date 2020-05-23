//
// Created by Keri Southwood-Smith on 05 February 2020.
//
#include "Controller.h"

bool Controller::collisionCheckAABB(const Brick &ccBrick) {
    if (ccBrick.isDestroyed()) {
        return false;
    }
    SDL_Rect ballPos  = ball.getPosition();
    SDL_Rect brickPos = ccBrick.getEdges();

    int ballMin  = ballPos.x;
    int ballMax  = ballPos.x + ballPos.w - 1;
    int brickMin = brickPos.x;
    int brickMax = brickPos.w;

    ballMin = ballMin < brickMin ? brickMin : ballMin;
    ballMax = ballMax > brickMax ? brickMax : ballMax;

    if (ballMax <= ballMin) {
        return false;
    }

    ballMin  = ballPos.y;
    ballMax  = ballPos.y + ballPos.h - 1;
    brickMin = brickPos.y;
    brickMax = brickPos.h;

    ballMin = ballMin < brickMin ? brickMin : ballMin;
    ballMax = ballMax > brickMax ? brickMax : ballMax;

    return ballMax > ballMin;
}

bool Controller::collisionCheckCircle(const Brick &ccBrick) {
    if (ccBrick.isDestroyed()) {
        return false;
    }

    SDL_Rect ballPos  = ball.getPosition();
    SDL_Rect brickPos = ccBrick.getBounds();

    SDL_Point ballCtr  = {ballPos.x + (ballPos.w / 2),
                         ballPos.y + (ballPos.h / 2)};
    SDL_Point brickCtr = {brickPos.x + (brickPos.w / 2),
                          brickPos.y + (brickPos.h / 2)};

    SDL_Point distance = {abs(ballCtr.x - brickCtr.x),
                          abs(ballCtr.y - brickCtr.y)};

    // center of circle is too far away on X or Y axis
    if ((distance.x > (brickPos.w / 2) + (ballPos.w / 2)) ||
        (distance.y > (brickPos.h / 2) + (ballPos.h / 2))) {
        return false;
    }

    if ((distance.x <= (brickPos.w / 2) + (ballPos.w / 2)) ||
        (distance.y <= (brickPos.h / 2) + (ballPos.h / 2))) {
        return true;
    }

    unsigned int distance_squared = ((distance.x - (brickPos.w / 2)) ^ 2) +
                                    ((distance.y - (brickPos.h / 2)) ^ 2);

    if (distance_squared <= ((ballPos.w / 2) ^ 2)) {
        return true;
    }

    return false;
}

void Controller::bounceBall(Brick &bBrick) {
    SDL_Log("********** bounceBall() **********");
    SDL_Rect ballPos  = ball.getPosition();
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
        ball.flipYDir();
        std::cout << "ballB >= brickB, flipY" << std::endl;
    }
    if (ballT <= brickT) {
        ball.flipYDir();
        std::cout << "ballT <= brickT, flipY" << std::endl;
    }
    if (ballL <= brickL) {
        ball.flipXDir();
        std::cout << "ballL <= brickL, flipX" << std::endl;
    }
    if (ballR >= brickR) {
        ball.flipXDir();
        std::cout << "ballR >= brickR, flipX" << std::endl;
    }
}

void Controller::paddleCollision() {
    const SDL_Rect ball_pos = ball.getPosition();
    const SDL_Rect padd_pos = paddle.getPosition();

    if (ball_pos.y < padd_pos.y - ball_pos.h + 3) {
        if (ball.getYDir() == Ball::DIR_DOWN) {
            ball.flipYDir();
        }

        if (ball_pos.x < padd_pos.x + padd_pos.w / 2) {
            if (ball.getXDir() > 0.0f) {
                ball.flipXDir();
            }
        } else {
            if (ball.getXDir() < 0.0f) {
                ball.flipXDir();
            }
        }
    }
}

int Controller::clamp(int value, int min, int max) {
    return std::max(min, std::min(max, value));
}