//
// Created by theom on 10/6/2020.
//

#ifndef LED_BOARD_PROGRAM_ANTCONSTANTS_HPP
#define LED_BOARD_PROGRAM_ANTCONSTANTS_HPP
#include <utility>

enum Direction {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    NUM_DIRECTIONS = LEFT + 1
};

const std::pair<int, int> REMOVE_ANT_SIGNAL = std::make_pair(-1,-1);

const std::pair<int, int> DIR_SHIFT_VALUES[] = {
        std::make_pair(-1,0),
        std::make_pair(0,1),
        std::make_pair(1,0),
        std::make_pair(0,-1)
};
#endif //LED_BOARD_PROGRAM_ANTCONSTANTS_HPP
