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

Controller::Controller(Led led, Locomotion locomotion, Rc rc) : led(led),locomotion(locomotion),rc(rc){
    // TODO: Adicionar a lógica de construção do objeto
}

void Controller::run() {
    switch (this->current_state) {
        case STRATEGY_CHOOSER: {
            // TODO: Implementar a lógica de escolha de estratégia
            break;
        }
        case RUN: {
            // TODO: Implementar a lógica de execução da estratégia
            break;
        }
        default: {
            // TODO: Implementar a lógica de estado padrão
            locomotion.stop();
            led.off();
            break;
        }
    }
}

void Controller::move_robot(Direction direction) {
    switch (direction) {
        // TODO: Implementar a lógica de movimentação do robô
        case FORWARD: {
            break;
        }
        case BACKWARD: {
            break;
        }
        case LEFT: {
            break;
        }
        case RIGHT: {
            break;
        }
        case STOPPED: {
            break;
        }
        case RC_INPUT: {
            break;
        }
        default: {
            break;
        }
    }
}

void Controller::strategy_run() {
    switch (this->current_level) {
        case LEVEL_0: {
            // TODO: Implementar a lógica de execução da estratégia 0
            break;
        }
        case LEVEL_1: {
            // TODO: Implementar a lógica de execução da estratégia 1
            break;
        }
        case LEVEL_2: {
            // TODO: Implementar a lógica de execução da estratégia 2
            break;
        }
        case LEVEL_3: { //giro 180º
            // TODO: Implementar a lógica de execução da estratégia 3
            uint32_t turn_start_time = 0;
            const uint32_t TURN_180_TIME_MS = 300;
            if (turn_start_time == 0) {
                turn_start_time = HAL_GetTick();
                locomotion.set_speed(-100, 100);
        }

            if (HAL_GetTick() - this->turn_start_time >= this->TURN_180_TIME_MS) {
                locomotion.stop();
                turn_start_time = 0;
                current_state = RUN; //volta para cá caso o tempo seja menor do que 300ms ainda
            }
            break;

        }
        default: {
            break;
        }
    }
}
