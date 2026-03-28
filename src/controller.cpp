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
    //this->current_level = LEVEL_3;
}

void Controller::init() {
    this->current_state = INIT;
}

void Controller::run() {
    switch (this->current_state) {
        case STRATEGY_CHOOSER: {
            // TODO: Implementar a lógica de escolha de estratégia) {
            this->set_next_strategy();
            this->current_state = RUN;
            led.off();
            break;
        }
        case RUN: {
            // TODO: Implementar a lógica de execução da estratégia
            this->strategy_run();
            this->current_state = INIT;
            break;
        }
        case INIT: {
            // TODO: Implementar a lógica de estado padrão
            if (!((rc.get_speed_ch1() == 100 || rc.get_speed_ch1() == -100) && (rc.get_speed_ch2() == 100 || rc.get_speed_ch2() == -100))) {
                this->move_robot(RC_INPUT);
            } else {
                this->current_state = STRATEGY_CHOOSER;
                led.on();
                hal::mcu::sleep(2000);
                led.off();
            }
            break;
        }
        case STOP: {
            break;
        }
    }
}

void Controller::move_robot(Direction turn) {
    /*led.on();
    hal::mcu::sleep(2000);
    led.off();
    hal::mcu::sleep(2000);*/
    /*switch (turn) {
        // TODO: Implementar a lógica de movimentação do robô
        case SLOW_FOWARD: {
            locomotion.set_speed(35, 35);
            break;
        }
        case FORWARD: {
            locomotion.set_speed(70,70);
            break;
        }
        case BACKWARD: {
            locomotion.set_speed(-70,-70);
            break;
        }
        case LEFT: {
            locomotion.set_speed(-70, 70);
            break;
        }
        case RIGHT: {
            locomotion.set_speed(70, -70);
            break;
        }
        case STOPPED: {
            locomotion.stop();
            break;
        }
        case RC_INPUT: {*/
            /*channel_1 = -rc.get_speed_ch1();
        	channel_2 = rc.get_speed_ch2();

        	left_speed = channel_1 + channel_2;
        	right_speed = channel_1 - channel_2;

        	left_speed = constrain(left_speed, -70, 70);
        	right_speed = constrain(right_speed, -70, 70);
        	locomotion.set_speed(left_speed, right_speed);*/
            this->locomotion.set_speed(this->rc.get_speed_ch1(),this->rc.get_speed_ch2());
            /*break;
        }
        default: {
            break;
        }
    }*/
}

void Controller::move_timer(Direction direction, uint16_t time_elapsed) {
    this->move_robot(direction);
    hal::mcu::sleep(time_elapsed);
    this->move_robot(STOPPED);
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
            const uint16_t TURN_LEFT_TIMER = 60;
            const uint16_t TURN_RIGHT_TIMER = 120;
            const uint16_t TINY_STRAIGHT_TIMER = 100;
            const uint16_t NORMAL_STRAIGHT_TIMER = 500;

            this->move_timer(LEFT, TURN_LEFT_TIMER);
            this->move_timer(SLOW_FOWARD, TINY_STRAIGHT_TIMER);
            this->move_timer(RIGHT, TURN_RIGHT_TIMER);
            this->move_timer(FORWARD, NORMAL_STRAIGHT_TIMER);

            break;
        }
        case LEVEL_1: { //zigue-zague
            // TODO: Implementar a lógica de execução da estratégia 1
            const uint16_t TURN_TINY_TIMER = 60;
            const uint16_t TURN_BIG_TIMER = 120;
            const uint16_t STRAIGHT_TIMER = 400;

            this->move_timer(RIGHT, TURN_TINY_TIMER);
            this->move_timer(FORWARD, STRAIGHT_TIMER);
            this->move_timer(LEFT, TURN_BIG_TIMER);
            this->move_timer(FORWARD, 2*STRAIGHT_TIMER);
            this->move_timer(RIGHT, TURN_BIG_TIMER);
            this->move_timer(FORWARD, STRAIGHT_TIMER);
            this->move_timer(LEFT, TURN_TINY_TIMER);

            break;
        }
        case LEVEL_2: { //chute
            // TODO: Implementar a lógica de execução da estratégia 2
            const uint16_t AJUSTEZINHO_TIME = 50;
            const uint16_t TURN_90_TIME_MS = 250;
            led.on();
            hal::mcu::sleep(2000);
            led.off();
            this->move_timer(RIGHT, AJUSTEZINHO_TIME);
            led.on();
            hal::mcu::sleep(2000);
            led.off();
            this->move_timer(LEFT, TURN_90_TIME_MS);
            led.on();
            hal::mcu::sleep(2000);
            led.off();

            break;
        }
        case LEVEL_3: { //giro 180º
            // TODO: Implementar a lógica de execução da estratégia 3
            const uint16_t TURN_180_TIME_MS = 500;

            this->move_timer(RIGHT, TURN_180_TIME_MS);
            break;

        }
        default: {
            break;
        }
    }
}
