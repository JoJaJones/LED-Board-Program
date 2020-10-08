//
// Created by theom on 10/7/2020.
//

#include "BigAnt.hpp"

BigAnt::BigAnt(int size, std::pair<int, int> pos, Direction dir, Behaviors bx, LEDBoard::Colors color)
      : Ant(pos, dir, bx, color){
    this->size = size;
    hasMovedThisStep = 0;
}

BigAnt::BigAnt(int size, std::pair<int, int> pos, Direction dir, MoveBehavior *move, TurnBehavior *turn,
               EdgeBehavior *edge, LEDBoard::Colors color)
               : Ant(pos, dir, move, turn, edge, color){
    this->size = size;
    hasMovedThisStep = 0;
}

Ant *BigAnt::move_ant(int color) {
    // if ant hasn't been moved this turn move it
    if (hasMovedThisStep < 1) {
        Ant::move_ant(color);
    }

    // if every position the ant occupies has been touched reset hasMoved
    hasMovedThisStep++;
    if (hasMovedThisStep == size*size){
        hasMovedThisStep = 0;
    }
}

std::vector<std::pair<int, int>> *BigAnt::getPos() {
    auto *positions = new std::vector<std::pair<int, int>>();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            positions->emplace_back(pos.first + i, pos.second + j);
        }
    }
    return positions;
}


