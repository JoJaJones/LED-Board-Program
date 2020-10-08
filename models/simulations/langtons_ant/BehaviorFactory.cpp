//
// Created by theom on 10/7/2020.
//

#include "BehaviorFactory.hpp"
BehaviorFactory* BehaviorFactory::bxFactory = nullptr;

BehaviorFactory * BehaviorFactory::getInstance() {
    if (bxFactory == nullptr) {
        bxFactory = new BehaviorFactory();
    }
    return bxFactory;
}

BehaviorFactory::BehaviorFactory() {
    antSettings = AntDataService::getInstance();
}

BehaviorFactory::~BehaviorFactory() {
    bxFactory = nullptr;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
MoveBehavior *BehaviorFactory::createMoveBx(int moveDistance) {
    return new MoveBehavior(moveDistance);
}
#pragma clang diagnostic pop

TurnBehavior *BehaviorFactory::createTurnBx(int turnType) {
    return new TurnBehavior(turnType, antSettings->getNumColors());
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
EdgeBehavior *BehaviorFactory::createEdgeBx(EdgeType type, MoveBehavior *moveBx, TurnBehavior *turnBx) {
    EdgeBehavior *edgeBx;
    switch (type) {
        case WALL: edgeBx = new Wall();
            break;
        case DEATH: edgeBx = new Death();
            break;
        case REMOVE: edgeBx = new Death(true);
            break;
        case TELEPORT: edgeBx = new Teleport();
            break;
        case UTURN: edgeBx = new UTurn();
            break;
        case RANDOM_TELEPORT: edgeBx = new RandomTeleport();
    }

    edgeBx->setMoveBehavior(moveBx);
    edgeBx->setTurnBehavior(turnBx);
    return edgeBx;
}
#pragma clang diagnostic pop

Behaviors BehaviorFactory::createBehaviors(EdgeType type, int turnType, int moveDistance) {
    Behaviors antBx{};
    antBx.moveBX = createMoveBx(moveDistance);
    antBx.turnBx = createTurnBx(turnType);
    antBx.edgeBx = createEdgeBx(type, antBx.moveBX, antBx.turnBx);
    return antBx;
}


