/**
 * @file test_locomotion.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Test for locomotion class.
 *
 * @date 04/2025
 */

#include "motor.hpp"
#include "mcu.hpp"
#include "target.hpp"
#include "led.hpp"
#include "locomotion.hpp"

int main() {
    // TODO: Adicionar a lógica de teste para os motores.

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

    Locomotion locomotion(motor_left, motor_right);

    for (;;) {
        locomotion.set_speed(50, -50);

        led.on();

        hal::mcu::sleep(3000);

        locomotion.stop();

        led.off();

        hal::mcu::sleep(2000);

        locomotion.set_speed(-50, 50);

        led.on();

        hal::mcu::sleep(3000);
    }
}
