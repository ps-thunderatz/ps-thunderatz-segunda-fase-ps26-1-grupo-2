#include <cstdint>
#include "led.hpp"
#include "rc.hpp"
#include "mcu.hpp"
#include "target.hpp"
#include "motor.hpp"
#include "utils.hpp"
#include "locomotion.hpp"
#include "controller.hpp"


int main() {
    hal::mcu::init();

    Led led(LED_PORT, LED_PIN);
    led.on();

    Motor leftMotor(
        MOTORS_TIM_INIT, MOTORS_TIM_HANDLER, LEFT_MOTOR_FORWARD_TIM_CH, MOTORS_TIM_HANDLER, LEFT_MOTOR_BACKWARD_TIM_CH
    );

    Motor rightMotor(
        MOTORS_TIM_INIT, MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH, MOTORS_TIM_HANDLER,
        RIGHT_MOTOR_BACKWARD_TIM_CH
    );

    Locomotion locomotion(leftMotor, rightMotor);

    Rc rc(RC_RECEIVER_TIM_INIT, &RC_RECEIVER_CH1_TIM_HANDLER, RC_RECEIVER_CH1_TIM_CH, RC_RECEIVER_CH2_TIM_CH);

    Controller controller(led, locomotion, rc);

    for (;;) {
        controller.run();
    }
    return 0;
}
