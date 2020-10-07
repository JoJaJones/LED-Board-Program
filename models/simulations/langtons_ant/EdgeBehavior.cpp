//
// Created by theom on 10/6/2020.
//

#include "EdgeBehavior.hpp"

std::pair<int, int> EdgeBehavior::adjustPos(std::pair<int, int> nextPos) {
    if(nextPos.first < 0){
        nextPos.first = 0;
    } else if (nextPos.first >= LEDBoard::PIXEL_ROWS){
        nextPos.first = LEDBoard::PIXEL_ROWS - 1;
    }

    if(nextPos.second < 0){
        nextPos.second = 0;
    } else if (nextPos.second >= LEDBoard::PIXEL_COLS) {
        nextPos.second = LEDBoard::PIXEL_COLS - 1;
    }

    return nextPos;
}

bool EdgeBehavior::isEdge(std::pair<int, int> curPos, Direction direction) {
    std::pair<int, int> nextPos = moveBehavior->move(curPos, direction);
    if(nextPos.first < 0 || nextPos.second < 0){
        return true;
    }

    if(nextPos.first > LEDBoard::PIXEL_ROWS || nextPos.second > LEDBoard::PIXEL_COLS){
        return true;
    }

    return false;
}

void EdgeBehavior::setMoveBehavior(MoveBehavior *moveBx) {
    this->moveBehavior = moveBx;
}

void EdgeBehavior::setTurnBehavior(TurnBehavior *turnBx) {
    this->turnBehavior = turnBx;
}

std::pair<int, int> Teleport::handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal) {
    std::pair<int, int> nextPos = moveBehavior->move(curPos, direction);

    nextPos.first += LEDBoard::PIXEL_ROWS;
    nextPos.first %= LEDBoard::PIXEL_ROWS;

    nextPos.second += LEDBoard::PIXEL_COLS;
    nextPos.second %= LEDBoard::PIXEL_COLS;

    return nextPos;
}

std::pair<int, int> UTurn::handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal) {
    std::pair<int, int> nextPos = adjustPos(moveBehavior->move(curPos, direction));

    direction = static_cast<Direction>((direction + NUM_DIRECTIONS / 2) % NUM_DIRECTIONS);

    return nextPos;
}

Death::Death(bool remove) {
    removeOnDeath = remove;
}

std::pair<int, int> Death::handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal) {
    std::pair<int, int> nextPos = adjustPos(moveBehavior->move(curPos, direction));

    if(removeOnDeath){
        nextPos = std::make_pair(-1,-1);
    }

    moveBehavior->setMoveDistance();

    return nextPos;
}


std::pair<int, int> Wall::handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal) {
    std::pair<int, int> nextPos;

    // if ant not at the edge move there first
    if(std::min(curPos.first, curPos.second) - 1 >= 0 && curPos.first + 1 < LEDBoard::PIXEL_ROWS
            && curPos.second + 1 < LEDBoard::PIXEL_COLS) {
        nextPos = adjustPos(moveBehavior->move(curPos, direction));
    } else {
        nextPos = curPos;

        // while loop to prevent getting stuck in the corners
        while (isEdge(curPos, direction)) {
            direction = turnBehavior->turn(colorVal, direction);
        }
    }
    return nextPos;
}

RandomTeleport::RandomTeleport(int antSize)
    : rowRange(0, LEDBoard::PIXEL_ROWS - antSize), colRange(LEDBoard::PIXEL_COLS - antSize) {}

std::pair<int, int> RandomTeleport::handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal) {
    return std::make_pair(rowRange(randGen), colRange(randGen));
}


