//
// Created by theom on 10/6/2020.
//

#ifndef LED_BOARD_PROGRAM_MOVEBEHAVIOR_HPP
#define LED_BOARD_PROGRAM_MOVEBEHAVIOR_HPP

#include "antconstants.hpp"

class MoveBehavior {
private:
    int moveDistance;

public:
    explicit MoveBehavior(int moveDist);
    std::pair<int, int> move(std::pair<int, int> &pos, Direction dir);
    void setMoveDistance(int newDistance = 0);
    int getMoveDistance();
};


#endif //LED_BOARD_PROGRAM_MOVEBEHAVIOR_HPP