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
        case LEVEL_3: {
            // TODO: Implementar a lógica de execução da estratégia 3
        }
        default: {
            break;
        }
    }
}
