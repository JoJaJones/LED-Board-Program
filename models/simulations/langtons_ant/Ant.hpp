//
// Created by theom on 10/5/2020.
//

#ifndef LED_BOARD_PROGRAM_ANT_HPP
#define LED_BOARD_PROGRAM_ANT_HPP


#include "EdgeBehavior.hpp"
#include <constants.hpp>
#include "BehaviorFactory.hpp"

class Ant {
protected:
    MoveBehavior *moveBx = nullptr;
    TurnBehavior *turnBx = nullptr;
    EdgeBehavior *edgeBx = nullptr;
    std::pair<int, int> pos;
    Direction heading;
    LEDBoard::Colors color;
    void sanitizeSettings();
    static void sanitizeSetting(int &posValue);
    static void sanitizeSetting(Direction &heading);
    static void sanitizeSetting(MoveBehavior *&move);
    static void sanitizeSetting(TurnBehavior *&turn);
    void sanitizeSetting(EdgeBehavior *&edge);
public:
    Ant(std::pair<int,int> pos, Direction dir, Behaviors bx, LEDBoard::Colors color);
    Ant(std::pair<int,int> pos, Direction dir, MoveBehavior *move,
        TurnBehavior *turn, EdgeBehavior *edge, LEDBoard::Colors color);
    virtual ~Ant();
    virtual Ant* move_ant(int color);
    virtual std::vector<std::pair<int, int>> * getPos();
    bool isDead();
    void changeDirection(int color);
    void setMoveDistance(int distance);
    void setEdgeBx(EdgeBehavior *edgeBehavior);
    void setTurnBehavior(TurnBehavior *turnBehavior);
};


#endif //LED_BOARD_PROGRAM_ANT_HPP
