//
// Created by theom on 10/6/2020.
//

#ifndef LED_BOARD_PROGRAM_TURNBEHAVIOR_HPP
#define LED_BOARD_PROGRAM_TURNBEHAVIOR_HPP


#include <vector>
#include "antconstants.hpp"

class TurnBehavior {
private:
    std::vector<int> dirMods;
    int turnType, numColors;

    void loadDirMods();

public:
    std::vector<int>* getdirMods();
    TurnBehavior(int turnType, int numColors);
    Direction turn(int colorVal, Direction dir);
};


#endif //LED_BOARD_PROGRAM_TURNBEHAVIOR_HPP
