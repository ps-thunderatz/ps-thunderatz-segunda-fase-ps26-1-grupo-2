/**
 * @file motor.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Motor class implementation.
 *
 * @date 06/2024
 */

#include "motor.hpp"
#include "utils.hpp"

#define BREAK_SPEED_THRESHOLD 5

Motor::Motor(
    void (*tim_init)(), TIM_HandleTypeDef* forward_tim_handle, uint8_t forward_tim_ch,
    TIM_HandleTypeDef* backward_tim_handle, uint8_t backward_tim_ch, int8_t min_speed, int8_t max_speed
) : forward_tim_handle(forward_tim_handle), forward_tim_ch(forward_tim_ch),
    backward_tim_handle(backward_tim_handle), backward_tim_ch(backward_tim_ch),
    min_speed(min_speed), max_speed(max_speed) {
    // Implemente aqui o criador da classe Motor.

    tim_init();
    HAL_TIM_PWM_Start(forward_tim_handle, forward_tim_ch);
    HAL_TIM_PWM_Start(backward_tim_handle, backward_tim_ch);
}

void Motor::set_speed(int8_t speed) {
    // Implemente aqui a função para definir a velocidade do motor.

    speed = map(speed, -100, 100, min_speed, max_speed); //erro aqui
    int8_t stop_threshold = min_speed/20;
    if (speed >= -1*(stop_threshold) && speed <= stop_threshold) { stop();
    } else if (speed < 0) {
        __HAL_TIM_SET_COMPARE(forward_tim_handle, forward_tim_ch, 0);
        __HAL_TIM_SET_COMPARE(backward_tim_handle, backward_tim_ch, -speed);
    } else {
        __HAL_TIM_SET_COMPARE(forward_tim_handle, forward_tim_ch, speed);
        __HAL_TIM_SET_COMPARE(backward_tim_handle, backward_tim_ch, 0);
    }
}

void Motor::stop() {
    // Implemente aqui a função para parar o motor.

    __HAL_TIM_SET_COMPARE(forward_tim_handle, forward_tim_ch, 1000);
    __HAL_TIM_SET_COMPARE(backward_tim_handle, backward_tim_ch, 1000);
}
