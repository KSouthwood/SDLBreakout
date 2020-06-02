//
// Created by Keri Southwood-Smith on 05 February 2020.
//
#include "Controller.h"

bool Controller::collisionCheckCircle(const Brick &a_brick) {
    // get center point of ball and corner points of the brick
    auto ball_pos  = ball.getPosition();
    auto brick_pos = a_brick.getEdges();

    // calculate nearest point on brick edge to center of the ball
    SDL_Point coll_point = {clamp(ball_pos.x, brick_pos.x, brick_pos.w),
                            clamp(ball_pos.y, brick_pos.y, brick_pos.h)};

    // calculate the square of the distance between the nearest point and the ball center
    SDL_FPoint diff = {static_cast<float>(coll_point.x) - ball_pos.x, static_cast<float>(coll_point.y) - ball_pos.y};
    float dist_square = (diff.x * diff.x) + (diff.y * diff.y);

    // we have a collision if the square of the distance is less than the radius square
    if (dist_square < (ball.getRadius() * ball.getRadius())) {
        SDL_FPoint compass[4] = {{0.0f, 1.0f},   // ball direction is heading DOWN
                                 {1.0f, 0.0f},   // ball direction is heading RIGHT
                                 {0.0f, -1.0f},  // ball direction is heading UP
                                 {-1.0f, 0.0f}}; // ball direction is heading LEFT
        // get the length of the difference between the nearest point and the ball center...
        float length = sqrt(dist_square);
        // ...then normalize it (get a unit vector: vector with a length of 1)
        SDL_FPoint unit_vec = { diff.x / length, diff.y / length };

        // determine which side of the rectangle we collided with
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
                ball.setYDir(-(ball.getYDir()));
                break;
            case 1: // RIGHT
            case 3: // LEFT
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Flipping X direction from %f to %f.", ball.getXDir(), -ball.getXDir());
                ball.setXDir(-(ball.getXDir()));
                break;
            default:
                break;
            }
            return true;
    } else {
        return false;
    }
}

/*
 * Determine if we have collided with the paddle, then change the ball direction
 * depending where on the paddle we hit. Amount of change depends on how far
 * from the paddle center the ball hits.
 */
void Controller::paddleCollision() {
    const auto ball_pos   = ball.getPosition();
    const auto paddle_pos = paddle.getPosition();

    if (ball_pos.y < static_cast<float>(paddle_pos.y) - ball.getRadius() + 3) {
        SDL_Log("Ball collision with paddle.");
        SDL_Log("Old direction: %f, %f", ball.getXDir(), ball.getYDir());

        // determine how far from center of paddle the ball hits the paddle
        float paddle_center = static_cast<float>(paddle_pos.x) + static_cast<float>(paddle_pos.w) / 2.0f;
        float distance = ball_pos.x - paddle_center;
        float percentage = distance / (static_cast<float>(paddle_pos.w) / 2.0f);

        // calculate new direction for ball
        float strength = 2.0f;
        SDL_FPoint old_velocity = {ball.getXDir(), ball.getYDir()}; // save old direction
        ball.setXDir(1.0f * percentage * strength);
        // get lengths of old and new direction vectors
        float old_length = std::sqrt(old_velocity.x * old_velocity.x + old_velocity.y * old_velocity.y);
        float new_length = std::sqrt(ball.getXDir() * ball.getXDir() + ball.getYDir() * ball.getYDir());
        // normalize new direction vector
        SDL_FPoint unit_vec = {ball.getXDir() / new_length, ball.getYDir() / new_length};
        // set x direction keeping velocity constant
        ball.setXDir(unit_vec.x * old_length);
        ball.setYDir(-1.0f * std::abs(ball.getYDir()));
        SDL_Log("New direction: %f, %f", ball.getXDir(), ball.getYDir());
    }
}

int Controller::clamp(float f_value, int min, int max) {
    int value = static_cast<int>(f_value);
    return std::max(min, std::min(max, value));
}