//
// Created by theom on 10/6/2020.
//

#ifndef LED_BOARD_PROGRAM_EDGEBEHAVIOR_HPP
#define LED_BOARD_PROGRAM_EDGEBEHAVIOR_HPP


#include "TurnBehavior.hpp"
#include "MoveBehavior.hpp"
#include <board_constants.hpp>
#include <algorithm>
#include <random>

class EdgeBehavior {
protected:
    MoveBehavior *moveBehavior = nullptr;
    TurnBehavior *turnBehavior = nullptr;

    std::pair<int, int> adjustPos(std::pair<int, int> nextPos);
public:
    bool isEdge(std::pair<int, int> curPos, Direction direction);
    virtual std::pair<int, int> handleEdge(std::pair<int, int> curPos,
                                           Direction &direction, int colorVal) = 0;
    void setMoveBehavior(MoveBehavior *moveBx);
    void setTurnBehavior(TurnBehavior *turnBx);
};

class Teleport : public EdgeBehavior {
public:
    std::pair<int, int> handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal) override;
};

class UTurn : public EdgeBehavior {
public:
    std::pair<int, int> handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal) override;
};

class Death : public EdgeBehavior {
private:
    bool removeOnDeath;

public:
    explicit Death(bool remove = false);
    std::pair<int, int> handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal) override;
};

class Wall : public EdgeBehavior {
public:
    std::pair<int, int> handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal) override;
};

class RandomTeleport : EdgeBehavior {
private:
    std::default_random_engine randGen;
    std::uniform_int_distribution<int> rowRange;
    std::uniform_int_distribution<int> colRange;

public:
    explicit RandomTeleport(int antSize = 1);
    std::pair<int, int> handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal) override;
};

#endif //LED_BOARD_PROGRAM_EDGEBEHAVIOR_HPP
