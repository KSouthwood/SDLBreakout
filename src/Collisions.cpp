//
// Created by Keri Southwood-Smith on 05 February 2020.
//
#include "Controller.h"

bool Controller::collisionCheckCircle(const Brick &a_brick) {
    if (a_brick.isDestroyed()) {
        return false;
    }

    SDL_Rect ball_pos  = ball.getBounds();
    SDL_Rect brick_pos = a_brick.getEdges();

    SDL_Point ball_ctr = {ball_pos.x + (ball_pos.w / 2),
                          ball_pos.y + (ball_pos.h / 2)};

    SDL_Point coll_point = {clamp(ball_ctr.x, brick_pos.x, brick_pos.w),
                            clamp(ball_ctr.y, brick_pos.y, brick_pos.h)};

    SDL_FPoint diff = {static_cast<float>(coll_point.x - ball_ctr.x), static_cast<float>(coll_point.y - ball_ctr.y)};
    float dist_square = (diff.x * diff.x) + (diff.y * diff.y);

    if (dist_square < (static_cast<float>(ball_pos.w * ball_pos.w) / 4.0f)) {
        SDL_FPoint compass[4] = {{0.0f, 1.0f},   // DOWN
                                 {1.0f, 0.0f},   // RIGHT
                                 {0.0f, -1.0f},  // UP
                                 {-1.0f, 0.0f}}; // LEFT
        float length = sqrt(dist_square);
        SDL_FPoint unit_vec = { diff.x / length, diff.y / length };

        float max = 0.0f;
        int best = -1;
        for (int i = 0; i < 4; ++i) {
            float dot_product = (unit_vec.x * compass[i].x) + (unit_vec.y * compass[i].y);
            if (dot_product > max) {
                max = dot_product;
                best = i;
            }
        }
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                     "Ball collision with brick at %d, %d from %d(%f).",
                     brick_pos.x, brick_pos.y, best, max);

        switch (best) {
            case 0: // DOWN
            case 2: // UP
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Flipping Y direction from %f to %f.", ball.getYDir(), -ball.getYDir());
                ball.flipYDir();
                break;
            case 1: // RIGHT
            case 3: // LEFT
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Flipping X direction from %f to %f.", ball.getXDir(), -ball.getXDir());
                ball.flipXDir();
                break;
            default:
                break;
            }
            return true;
    } else {
        return false;
    }
}

void Controller::paddleCollision() {
    const auto ball_pos   = ball.getBounds();
    const auto paddle_pos = paddle.getPosition();

    if (ball_pos.y < paddle_pos.y - ball_pos.h + 3) {
        SDL_Log("Ball collision with paddle.");
        if (ball.getYDir() == Ball::DIR_DOWN) {
            ball.flipYDir();
        }

        if (ball_pos.x < paddle_pos.x + paddle_pos.w / 2) {
            if (ball.getXDir() > 0.0f) {
                ball.flipXDir();
                SDL_Log("Ball rebounding to left.");
            }
        } else {
            if (ball.getXDir() < 0.0f) {
                ball.flipXDir();
                SDL_Log("Ball rebound to right.");
            }
        }
    }
}

int Controller::clamp(int value, int min, int max) {
    return std::max(min, std::min(max, value));
}