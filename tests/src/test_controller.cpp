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
#include "rc.hpp"
#include "controller.hpp"



int main() {
    // TODO: Adicionar a lógica de teste para os motores.

    hal::mcu::init();

    Led led(LED_PORT, LED_PIN);

    Rc rc(RC_RECEIVER_TIM_INIT, &RC_RECEIVER_CH1_TIM_HANDLER, RC_RECEIVER_CH1_TIM_CH, RC_RECEIVER_CH2_TIM_CH);

    Motor motor_left(
        MOTORS_TIM_INIT, MOTORS_TIM_HANDLER, LEFT_MOTOR_FORWARD_TIM_CH,
        MOTORS_TIM_HANDLER, LEFT_MOTOR_BACKWARD_TIM_CH, -100, 100
    );
    Motor motor_right(
        MOTORS_TIM_INIT, MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH,
        MOTORS_TIM_HANDLER, RIGHT_MOTOR_BACKWARD_TIM_CH, -100, 100
    );

    Locomotion locomotion(motor_left, motor_right);

    Controller controller(led, locomotion, rc);

    for(;;){
        //locomotion.set_speed(rc.get_speed_ch1(),rc.get_speed_ch2());
        controller.move_robot(Controller::RC_INPUT);
    }
}

extern "C" void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim) {
    Rc::handle_global_callback(htim);
}
