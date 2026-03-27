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
        MOTORS_TIM_HANDLER, LEFT_MOTOR_BACKWARD_TIM_CH, -100, 100
    );
    Motor motor_right(
        MOTORS_TIM_INIT, MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH,
        MOTORS_TIM_HANDLER, RIGHT_MOTOR_BACKWARD_TIM_CH, -100, 100
    );

    Locomotion locomotion(motor_left, motor_right);


    hal::mcu::sleep(5000);
    for (int i = 2; i > 0; i--) {
        locomotion.set_speed(70, -70);

        led.on();

        hal::mcu::sleep(1000);

        locomotion.stop();

        led.off();

        hal::mcu::sleep(2000);

        locomotion.set_speed(-70, 70);

        led.on();

        hal::mcu::sleep(1000);

        locomotion.stop();

        hal::mcu::sleep(2000);
    }
}
