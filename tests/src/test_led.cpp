/**
 * @file test_led.cpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Test for Led class.
 *
 * @date 06/2024
 */

#include "led.hpp"
#include "mcu.hpp"
#include "target.hpp"

int main() {
    // TODO: Adicionar a lógica de teste para o LED.

    hal::mcu::init();

    Led led(LED_PORT, LED_PIN, GPIO_PIN_RESET);

    for (;;) {
        hal::mcu::sleep(1000);
        led.on();
        hal::mcu::sleep(1000);
        led.off();
    }
}
