//
// Created by theom on 10/5/2020.
//

#include "Ant.hpp"

Ant::Ant(std::pair<int, int> pos, Direction dir, Behaviors bx, LEDBoard::Colors color) {
    this->pos = pos;
    this->heading = dir;
    this->edgeBx = bx.edgeBx;
    this->moveBx = bx.moveBX;
    this->turnBx = bx.turnBx;
    this->color = color;
}

Ant::Ant(std::pair<int, int> pos, Direction dir, MoveBehavior *move, TurnBehavior *turn, EdgeBehavior *edge,
         LEDBoard::Colors color) {
    this->pos = pos;
    this->heading = dir;
    this->edgeBx = edge;
    this->moveBx = move;
    this->turnBx = turn;
    this->color = color;
}


Ant::~Ant() {
    delete turnBx;
    delete moveBx;
    delete edgeBx;
}

void Ant::sanitizeSettings() {
    if (pos.first < 0 || pos.first >= LEDBoard::PIXEL_ROWS) {
        sanitizeSetting(pos.first);
    }

    if (pos.second < 0 || pos.second >= LEDBoard::PIXEL_COLS) {
        sanitizeSetting(pos.second);
    }

    if (moveBx == nullptr) {
        sanitizeSetting(moveBx);
    }

    if (turnBx == nullptr) {
        sanitizeSetting(turnBx);
    }

    if (edgeBx == nullptr) {
        sanitizeSetting(edgeBx);
    }

    if (heading >= NUM_DIRECTIONS || heading < 0) {
        sanitizeSetting(heading);
    }
}

void Ant::sanitizeSetting(int &posValue) {
    posValue = 0;
}

void Ant::sanitizeSetting(Direction &heading) {
    heading = UP;
}

void Ant::sanitizeSetting(MoveBehavior *&move) {
    move = BehaviorFactory::getInstance()->createMoveBx();
}

void Ant::sanitizeSetting(TurnBehavior *&turn) {
    turn = BehaviorFactory::getInstance()->createTurnBx(1);
}

void Ant::sanitizeSetting(EdgeBehavior *&edge) {
    edge = BehaviorFactory::getInstance()->createEdgeBx(TELEPORT, moveBx, turnBx);
}

Ant *Ant::move_ant(int color) {
    if (edgeBx->isEdge(pos, heading, 1)){
        pos = edgeBx->handleEdge(pos, heading, color);
    } else {
        pos = moveBx->move(pos, heading);
    }

    return this;
}

bool Ant::isDead() {
    return moveBx == nullptr || moveBx->getMoveDistance() == 0;
}

void Ant::changeDirection(int color) {
    heading = turnBx->turn(color, heading);
}

std::vector<std::pair<int, int>> * Ant::getPos() {
    return new std::vector<std::pair<int, int>>(1, pos);
}

void Ant::setEdgeBx(EdgeBehavior *edgeBehavior) {
    edgeBx = edgeBehavior;
}

void Ant::setTurnBehavior(TurnBehavior *turnBehavior) {
    turnBx = turnBehavior;
}

void Ant::setMoveDistance(int distance) {
    moveBx->setMoveDistance(distance);
}
