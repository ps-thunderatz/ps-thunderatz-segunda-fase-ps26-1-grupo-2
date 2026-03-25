/**
 * @file test_motors.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Test for Motors class.
 *
 * @date 06/2024
 */

#include "motor.hpp"
#include "mcu.hpp"
#include "target.hpp"
#include "led.hpp"

int main() {
    // TODO: Adicionar a lógica de teste para o motor.

    hal::mcu::init();

    Led led(LED_PORT, LED_PIN);

    Motor motor_left(
        MOTORS_TIM_INIT, MOTORS_TIM_HANDLER, LEFT_MOTOR_FORWARD_TIM_CH,
        MOTORS_TIM_HANDLER, LEFT_MOTOR_BACKWARD_TIM_CH, -700, 700
    );
    Motor motor_right(
        MOTORS_TIM_INIT, MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH,
        MOTORS_TIM_HANDLER, RIGHT_MOTOR_BACKWARD_TIM_CH, -700, 700
    );

    for (;;) {
        motor_left.set_speed(-50);
        motor_right.set_speed(50);

        led.on();

        hal::mcu::sleep(3000);

        motor_left.stop();
        motor_right.stop();

        led.off();

        hal::mcu::sleep(2000);

        motor_left.set_speed(50);
        motor_right.set_speed(-50);

        led.on();

        hal::mcu::sleep(3000);
    }
}
