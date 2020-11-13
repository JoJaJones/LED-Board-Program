/****************************************************************************************
 *
 ***************************************************************************************/
#include "MoveBehavior.hpp"

MoveBehavior::MoveBehavior(int moveDist) : moveDistance(moveDist){}

std::pair<int, int> MoveBehavior::move(std::pair<int, int> &pos, Direction dir, int distance) {
    if (distance < 0) {
        distance = moveDistance;
    }
    std::pair<int, int> newPos;
    newPos.first = pos.first + DIR_SHIFT_VALUES[static_cast<int>(dir)].first * distance;
    newPos.second = pos.second + DIR_SHIFT_VALUES[static_cast<int>(dir)].second * distance;
    return newPos;
}

void MoveBehavior::setMoveDistance(int newDistance) {
    moveDistance = newDistance;
}

int MoveBehavior::getMoveDistance() {
    return moveDistance;
}
