/**
 * @file controller.hpp
 *
 * @author Comp Thunderatz <comp@thunderatz.org>
 *
 * @brief Pedrinha Semi Auto Controller Finite State Machine header file.
 *
 * @date 04/2025
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "led.hpp"
#include "locomotion.hpp"
#include "rc.hpp"

/**
 * @brief Controller class.
 */
class Controller {
public:
    /**
     * @brief Construct a new Controller object.
     */
    Controller(Led led, Locomotion locomotion, Rc rc);

    /**
     * @brief Initialize controller.
     */
    void init();

    /**
     * @brief Run controller.
     */
    void run();

private:
    /**
     * @brief Controller states.
     */
    enum State {
        INIT,
        STRATEGY_CHOOSER,
        RUN,
        STOP,
    };

    /**
     * @brief Robot directions.
     */
    enum Direction {
        SLOW_FOWARD,
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        STOPPED,
        RC_INPUT,
    };

    enum Level : uint8_t {
        LEVEL_0,
        LEVEL_1,
        LEVEL_2,
        LEVEL_3,
    };

    /**
     * @brief Move the robot.
     *
     * @param direction Direction to move the robot.
     */
    void move_robot(Direction direction);

    void move_timer(uint32_t time_elapsed, Direction direction);

    /**
     * @brief Set the next strategy.
     */
    void set_next_strategy();

    /**
     * @brief Run the strategy.
     */
    void strategy_run();

    Led        led;
    Locomotion locomotion;
    Rc         rc;

    State     current_state = INIT;
    Direction turn = STOPPED;

    const uint8_t max_strategy = 3;
    uint8_t       current_level = 0;

};  // namespace controller

#endif  // CONTROLLER_HPP
