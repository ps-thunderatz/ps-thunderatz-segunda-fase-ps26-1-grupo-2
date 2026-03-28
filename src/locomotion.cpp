/**
 * @file locomotion.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief locomotion class implementation.
 *
 * @date 04/2025
 */

#include "locomotion.hpp"

Locomotion::Locomotion(Motor& motor_left, Motor& motor_right) : motor_left(motor_left), motor_right(motor_right) {
    // Implemente aqui o criador da classe Locomotion.
}

void Locomotion::set_speed(int8_t left_speed, int8_t right_speed) {
    // Implemente aqui a função para definir a velocidade da locomoção.

    motor_left.set_speed(left_speed);
    motor_right.set_speed(right_speed);
}

void Locomotion::stop() {
    // Implemente aqui a função para parar a locomoção.

    motor_left.stop();
    motor_right.stop();
}
