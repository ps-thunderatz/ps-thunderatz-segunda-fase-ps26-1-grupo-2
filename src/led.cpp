/**
 * @file led.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Led class implementation.
 *
 * @date 04/2025
 */

#include "led.hpp"

Led::Led(GPIO_TypeDef* port, uint16_t pin) : port(port), pin(pin) {
    // Implemente aqui o criador da classe Led.

    this->off();
}

void Led::on(void) {
    // Implemente aqui a função para ligar o led.

    HAL_GPIO_WritePin(this->port, this-> pin, GPIO_PIN_SET);
}

void Led::off(void) {
    // Implemente aqui a função para desligar o led.

    HAL_GPIO_WritePin(this->port, this-> pin, GPIO_PIN_RESET);
}

void Led::toggle(void) {
    // Implemente aqui a função para alternar o estado do led.

    HAL_GPIO_TogglePin(this->port, this->pin);
}
