//
// Created by theom on 9/25/2020.
//

#ifndef LED_BOARD_PROGRAM_BOARD_CONSTANTS_HPP
#define LED_BOARD_PROGRAM_BOARD_CONSTANTS_HPP
namespace LEDBoard {
    enum Rotations {
        NONE, CLOCKWISE, DOWN, COUNTERCLOCKWISE
    };

    const int LED_ROWS_PER_BOARD = 32;          // # of rows of LEDs per board
    const int LED_COLS_PER_BOARD = 32;          // # of cols of LEDs per board
    const int BOARD_CHAIN_LEN = 1;              // # of boards chained together
    const Rotations PANEL_CONFIGURATION[] = {NONE};   // rotational configuration for each board
    const int NUM_ROWS_OF_PANELS = 1;               // # of boards per row
    const int NUM_COLS_OF_PANELS = 1;               // # of boards per col

    const int PIXEL_ROWS = LED_ROWS_PER_BOARD * NUM_ROWS_OF_PANELS; // calculate y pixels
    const int PIXEL_COLS = LED_COLS_PER_BOARD * NUM_COLS_OF_PANELS; // calculate x pixels

    const int GPIO_SLOWDOWN = 4;
}
#endif //LED_BOARD_PROGRAM_BOARD_CONSTANTS_HPP
