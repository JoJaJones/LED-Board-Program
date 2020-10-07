//
// Created by theom on 10/6/2020.
//

#include "MoveBehavior.hpp"

MoveBehavior::MoveBehavior(int moveDist) : moveDistance(moveDist){}

std::pair<int, int> MoveBehavior::move(std::pair<int, int> &pos, Direction dir) {
    std::pair<int, int> newPos;
    newPos.first = pos.first + DIR_SHIFT_VALUES[static_cast<int>(dir)].first * moveDistance;
    newPos.second = pos.second + DIR_SHIFT_VALUES[static_cast<int>(dir)].second * moveDistance;
    return newPos;
}

void MoveBehavior::setMoveDistance(int newDistance) {
    moveDistance = newDistance;
}

int MoveBehavior::getMoveDistance() {
    return moveDistance;
}
