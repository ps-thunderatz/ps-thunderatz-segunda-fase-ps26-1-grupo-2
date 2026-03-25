/**
 * @file target.hpp
 *
 * @brief Configurations for TPM-Ant board.
 *
 * @date 09/2025
 */

#ifndef __TARGET_HPP__
#define __TARGET_HPP__

/*****************************************
 * Public Constants
 *****************************************/

/**
 * LEDS
 */

#define LED_PORT GPIOA
#define LED_PIN GPIO_PIN_4

/**
 * MOTORS
 *
 * @brief A timer that generates 4 kHz PWM signals to the motors H bridges.
 */
#define MOTORS_TIM_INIT MX_TIM2_Init
#define MOTORS_TIM_HANDLER (&htim2)

#define RIGHT_MOTOR_FORWARD_TIM_CH TIM_CHANNEL_1
#define RIGHT_MOTOR_BACKWARD_TIM_CH TIM_CHANNEL_2

#define LEFT_MOTOR_FORWARD_TIM_CH TIM_CHANNEL_3
#define LEFT_MOTOR_BACKWARD_TIM_CH TIM_CHANNEL_4

/**
 * COMMUNICATION WITH RECEPTOR
 *
 * @brief A timer with an 1 MHz clock source that captures rising and falling
 * edges to calculate the HIGH time of the PPM.
 *
 * @note The PPM signal's period is 20 ms, but the timer counter period must be
 * set to max (0xFFFF)
 *
 * @ref See STM32Guide section about reading PPMs signals.
 */
#define RC_RECEIVER_TIM_INIT MX_TIM3_Init

#define RC_RECEIVER_CH1_TIM_INSTANCE TIM3
#define RC_RECEIVER_CH1_TIM_HANDLER (htim3)
#define RC_RECEIVER_CH1_TIM_CH TIM_CHANNEL_1
#define RC_RECEIVER_ACTIVE_TIM_CH1 HAL_TIM_ACTIVE_CHANNEL_1
#define RC_RECEIVER_CH1_PORT GPIOA
#define RC_RECEIVER_CH1_PIN GPIO_PIN_6

#define RC_RECEIVER_CH2_TIM_INSTANCE TIM3
#define RC_RECEIVER_CH2_TIM_HANDLER (htim3)
#define RC_RECEIVER_CH2_TIM_CH TIM_CHANNEL_2
#define RC_RECEIVER_ACTIVE_TIM_CH2 HAL_TIM_ACTIVE_CHANNEL_2
#define RC_RECEIVER_CH2_PORT GPIOA
#define RC_RECEIVER_CH2_PIN GPIO_PIN_7

#endif  // __TARGET_HPP__
