/**
 * @file controller.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Rock SemiAuto Controller Finite State Machine.
 *
 * @date 04/2025
 */

#include "mcu.hpp"
#include "controller.hpp"

static volatile int16_t left_speed;
static volatile int16_t right_speed;
static volatile int16_t channel_1;
static volatile int16_t channel_2;

Controller::Controller(Led led, Locomotion locomotion, Rc rc) : led(led), locomotion(locomotion), rc(rc) {
    // TODO: Adicionar a lógica de construção do objeto
}

void Controller::run() {
    switch (this->current_state) {
        case STRATEGY_CHOOSER: {
            // TODO: Implementar a lógica de escolha de estratégia) {
            this->set_next_strategy();
            this->current_state = RUN;
            break;
        }
        case RUN: {
            // TODO: Implementar a lógica de execução da estratégia
            this->strategy_run();
            break;
        }
        default: {
            // TODO: Implementar a lógica de estado padrão
            if (rc.get_speed_ch1() == 100 || rc.get_speed_ch1() == -100 || rc.get_speed_ch2() == 100 || rc.get_speed_ch2() == -100) {
                this->current_state = STRATEGY_CHOOSER;
            } else {
                this->move_robot(RC_INPUT);
            }
            break;
        }
    }
}

void Controller::move_robot(Direction direction) {
    switch (direction) {
        // TODO: Implementar a lógica de movimentação do robô
        case SLOW_FOWARD: {
            locomotion.set_speed(50, 50);
            break;
        }
        case FORWARD: {
            locomotion.set_speed(99,99);
            break;
        }
        case BACKWARD: {
            locomotion.set_speed(-99,-99);
            break;
        }
        case LEFT: {
            locomotion.set_speed(-99, 99);
            break;
        }
        case RIGHT: {
            locomotion.set_speed(99, -99);
            break;
        }
        case STOPPED: {
            locomotion.stop();
            break;
        }
        case RC_INPUT: {
            channel_1 = -rc.get_speed_ch1()*1.33;
        	channel_2 = rc.get_speed_ch2()*1.25;

        	left_speed = channel_1 + channel_2;
        	right_speed = channel_1 - channel_2;

        	left_speed = constrain(left_speed, -100, 100);
        	right_speed = constrain(right_speed, -100, 100);
        	locomotion.set_speed(left_speed, right_speed);
            break;
        }
        default: {
            break;
        }
    }
}

void Controller::move_timer(Direction direction, uint32_t time_elapsed) {
    uint32_t turn_start_time = 0;
    if (turn_start_time == 0) {
        turn_start_time = HAL_GetTick();
        this->move_robot(direction);
    }
    if (HAL_GetTick() - turn_start_time >= time_elapsed) {
        locomotion.stop();
        turn_start_time = 0;
    }
}

void Controller::set_next_strategy() {
    if (rc.get_speed_ch1() == 100 && rc.get_speed_ch2() == 100) {
        this->current_level = LEVEL_0;
    } else if (rc.get_speed_ch1() == 100 && rc.get_speed_ch2() == -100) {
        this->current_level = LEVEL_1;
    } else if (rc.get_speed_ch1() == -100 && rc.get_speed_ch2() == 100) {
        this->current_level = LEVEL_2;
    } else if (rc.get_speed_ch1() == -100 && rc.get_speed_ch2() == -100) {
        this->current_level = LEVEL_3;
    }
}

// Ajustes de timers necessario
void Controller::strategy_run() {
    switch (this->current_level) {
        case LEVEL_0: { //elastico
            // TODO: Implementar a lógica de execução da estratégia 0
            const uint32_t TURN_TIMER = 70;
            const uint32_t TINY_STRAIGHT_TIMER = 50;
            const uint32_t NORMAL_STRAIGHT_TIMER = 200;

            this->move_timer(LEFT, TURN_TIMER);
            this->move_timer(SLOW_FOWARD, TINY_STRAIGHT_TIMER);
            this->move_timer(RIGHT, TURN_TIMER);
            this->move_timer(FORWARD, NORMAL_STRAIGHT_TIMER);

            break;
        }
        case LEVEL_1: { //zigue-zague
            // TODO: Implementar a lógica de execução da estratégia 1
            const uint32_t TURN_TIMER = 70;
            const uint32_t STRAIGHT_TIMER = 100;

            this->move_timer(RIGHT, TURN_TIMER);
            this->move_timer(FORWARD, STRAIGHT_TIMER);
            this->move_timer(LEFT, TURN_TIMER);
            this->move_timer(FORWARD, STRAIGHT_TIMER);

            break;
        }
        case LEVEL_2: { //chute
            // TODO: Implementar a lógica de execução da estratégia 2
            const uint32_t AJUSTEZINHO_TIME = 50;
            const uint32_t TURN_90_TIME_MS = 150;

            this->move_timer(RIGHT, AJUSTEZINHO_TIME);
            this->move_timer(LEFT, TURN_90_TIME_MS);

            break;
        }
        case LEVEL_3: { //giro 180º
            // TODO: Implementar a lógica de execução da estratégia 3
            const uint32_t TURN_180_TIME_MS = 300;

            this->move_timer(RIGHT, TURN_180_TIME_MS);

            /*Imaginei que seria assim:
            uint32_t turn_start_time = 0;
            const uint32_t TURN_180_TIME_MS = 300;
            turn_start_time = HAL_GetTick();
            locomotion.set_speed(-100, 100);
            while(HAL_GetTick() - turn_start_time >= TURN_180_TIME_MS){
            }
            locomotion.stop();
            current_state = RUN; //volta para cá caso o tempo seja menor do que 300ms ainda
            */
            break;

        }
        default: {
            break;
        }
    }
}
