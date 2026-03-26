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
        MOTORS_TIM_INIT, MOTORS_TIM_HANDLER, RIGHT_MOTOR_FORWARD_TIM_CH, &MOTORS_TIM_HANDLER,
        RIGHT_MOTOR_BACKWARD_TIM_CH
    );

    Locomotion locomotion(leftMotor, rightMotor);

    Rc rc(RC_RECEIVER_TIM_INIT, RC_RECEIVER_CH1_TIM_HANDLER, RC_RECEIVER_CH1_TIM_CH, RC_RECEIVER_CH2_TIM_CH);

    Controller controller(led, locomotion, rc);

    uint32_t led_timer = HAL_GetTick();
    uint8_t led_blink_count = 0;

    for (;;) {
        controller.current_state = controller.RC_INPUT;
        controller.run();

        if (led_blink_count < 26 && HAL_GetTick() - led_timer >= 300) {
            led.toggle();
            led_timer = HAL_GetTick();
            led_blink_count++;
        }
    }
    return 0;
}

extern "C" void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim) {
    Rc::handle_global_callback(htim);
}
