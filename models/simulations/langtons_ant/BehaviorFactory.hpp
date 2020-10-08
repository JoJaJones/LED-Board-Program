//
// Created by theom on 10/7/2020.
//

#ifndef LED_BOARD_PROGRAM_BEHAVIORFACTORY_HPP
#define LED_BOARD_PROGRAM_BEHAVIORFACTORY_HPP


#include "MoveBehavior.hpp"
#include "TurnBehavior.hpp"
#include "AntDataService.hpp"
#include "EdgeBehavior.hpp"

class BehaviorFactory {
private:
    AntDataService *antSettings;
    static BehaviorFactory *bxFactory;
    BehaviorFactory();

public:
    ~BehaviorFactory();
    static BehaviorFactory *getInstance();
    MoveBehavior *createMoveBx(int moveDistance = 1);
    TurnBehavior *createTurnBx(int turnType = 1);
    EdgeBehavior *createEdgeBx(EdgeType type, MoveBehavior *moveBx, TurnBehavior * turnBx);
    Behaviors createBehaviors(EdgeType type = TELEPORT, int turnType = 1, int moveDistance = 1);
};


#endif //LED_BOARD_PROGRAM_BEHAVIORFACTORY_HPP
