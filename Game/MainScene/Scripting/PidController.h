//
// Created by EgorRychkov on 11.08.2025.
//

#ifndef LOGISTICHELL_PIDCONTROLLER_H
#define LOGISTICHELL_PIDCONTROLLER_H


class PidController {
public:
    PidController(float kp, float ki, float kd)
            : kp_(kp), ki_(ki), kd_(kd), prevError_(0.0f), integral_(0.0f) {}

    float update(float finish_value, float current_value, float dt) {
        float error = finish_value - current_value;

        float P = kp_ * error;
        integral_ += error * dt;
        float I = ki_ * integral_;
        float derivative = (error - prevError_) / dt;
        float D = kd_ * derivative;

        prevError_ = error;
        return P + I + D;
    }

    void reset() {
        prevError_ = 0.0f;
        integral_ = 0.0f;
    }

private:
    float kp_, ki_, kd_;
    float prevError_;
    float integral_;
};

#endif //LOGISTICHELL_PIDCONTROLLER_H
