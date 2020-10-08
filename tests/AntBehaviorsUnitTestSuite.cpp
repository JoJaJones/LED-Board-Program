//
// Created by Josh Jones on 10/6/2020.
//
#include <iostream>
#include <simulations/langtons_ant/MoveBehavior.hpp>
#include <cassert>
#include <vector>
#include <simulations/langtons_ant/TurnBehavior.hpp>
#include <simulations/langtons_ant/EdgeBehavior.hpp>

void testMoveBehavior();
void testTurnBehavior();
void testEdgeBehavior();
void testTeleportEdgeBehavior(EdgeBehavior *testEdge, MoveBehavior *moveBx);
void testUTurnEdgeBehavior(EdgeBehavior *testEdge, MoveBehavior *moveBx, TurnBehavior *turnBx);
void testWallEdgeBehavior(EdgeBehavior *testEdge, MoveBehavior *moveBx);
void testDeathEdgeBehavior(EdgeBehavior *testEdge, MoveBehavior *moveBx, TurnBehavior *turnBx);
void testRandomTeleportEdgeBehavior(EdgeBehavior *testEdge, MoveBehavior *moveBx);

using std::cout;
using std::endl;

int main() {
    cout<<"********************** Testing Move Behavior *********************"<<endl;
    testMoveBehavior();
    cout<<"******************* Move Behavior Tests Passed *******************"<<endl<<endl;

    cout<<"********************** Testing Turn Behavior *********************"<<endl;
    testTurnBehavior();
    cout<<"******************* Turn Behavior Tests Passed *******************"<<endl<<endl;

    cout<<"********************** Testing Edge Behavior *********************"<<endl;
    testEdgeBehavior();
    cout<<"******************* Edge Behavior Tests Passed *******************"<<endl<<endl;
    return 0;
}

void testMoveBehavior() {
    MoveBehavior testMove(1);
    std::pair<int, int> posStart(5,5);
    std::pair<int, int> posResult;

    posResult = testMove.move(posStart, UP );
    cout<<"Testing Up Movement"<<endl;
    assert(posStart.first - 1 == posResult.first && posStart.second == posResult.second);
    posResult = testMove.move(posStart, DOWN);
    cout<<"Testing Down Movement"<<endl;
    assert(posStart.first + 1 == posResult.first && posStart.second == posResult.second);
    posResult = testMove.move(posStart, RIGHT);
    cout<<"Testing Right Movement"<<endl;
    assert(posStart.first == posResult.first && posStart.second + 1 == posResult.second);
    posResult = testMove.move(posStart, LEFT);
    cout<<"Testing Left Movement"<<endl;
    assert(posStart.first == posResult.first && posStart.second - 1 == posResult.second);

    cout<<"Adjusting Movement Speed"<<endl;
    testMove.setMoveDistance(2);
    assert(testMove.getMoveDistance() == 2);

    posResult = testMove.move(posStart, UP);
    cout<<"Testing Up Movement"<<endl;
    assert(posStart.first - 2 == posResult.first && posStart.second == posResult.second);
    posResult = testMove.move(posStart, DOWN);
    cout<<"Testing Down Movement"<<endl;
    assert(posStart.first + 2 == posResult.first && posStart.second == posResult.second);
    posResult = testMove.move(posStart, RIGHT);
    cout<<"Testing Right Movement"<<endl;
    assert(posStart.first == posResult.first && posStart.second + 2 == posResult.second);
    posResult = testMove.move(posStart, LEFT);
    cout<<"Testing Left Movement"<<endl;
    assert(posStart.first == posResult.first && posStart.second - 2 == posResult.second);

    cout<<"Adjusting Movement Speed to 0"<<endl;
    testMove.setMoveDistance();
    assert(testMove.getMoveDistance() == 0);
}

void testTurnBehavior() {
    std::vector<int> *dirShifts;

    auto *testTurn = new TurnBehavior(1, 2);
    cout<<"Testing Dir Shift Loading (tT: 1, nC: 2)"<<endl;
    dirShifts = testTurn->getdirMods();
    assert((*dirShifts)[0] == 1);
    assert((*dirShifts)[1] == 3);
    delete testTurn;

    testTurn = new TurnBehavior(-1, 4);
    cout<<"Testing Dir Shift Loading (tT: -1, nC: 4)"<<endl;
    dirShifts = testTurn->getdirMods();
    assert((*dirShifts)[0] == 3);
    assert((*dirShifts)[1] == 1);
    assert((*dirShifts)[2] == 2);
    assert((*dirShifts)[3] == 0);
    delete testTurn;

    testTurn = new TurnBehavior(1, 3);
    cout<<"Testing Dir Shift Loading (tT: 1, nC: 3)"<<endl;
    dirShifts = testTurn->getdirMods();
    assert((*dirShifts)[0] == 1);
    assert((*dirShifts)[1] == 3);
    assert((*dirShifts)[2] == 2);
    delete testTurn;

    testTurn = new TurnBehavior(-1, 3);
    cout<<"Testing Dir Shift Loading (tT: -1, nC: 3)"<<endl;
    dirShifts = testTurn->getdirMods();
    assert((*dirShifts)[0] == 3);
    assert((*dirShifts)[1] == 1);
    assert((*dirShifts)[2] == 2);
    delete testTurn;

    testTurn = new TurnBehavior(1, 2);
    cout<<"Testing Turns (tT: 1, nC: 2)"<<endl;
    assert(testTurn->turn(0, UP) == RIGHT);
    assert(testTurn->turn(1, LEFT) == DOWN);
    delete testTurn;

    testTurn = new TurnBehavior(-1, 4);
    cout<<"Testing Turns (tT: -1, nC: 4)"<<endl;
    assert(testTurn->turn(0, UP) == LEFT);
    assert(testTurn->turn(1, UP) == RIGHT);
    assert(testTurn->turn(2, LEFT) == RIGHT);
    assert(testTurn->turn(3, DOWN) == DOWN);
    delete testTurn;

    testTurn = new TurnBehavior(1, 3);
    cout<<"Testing Turns (tT: 1, nC: 3)"<<endl;
    assert(testTurn->turn(0, UP) == RIGHT);
    assert(testTurn->turn(1, UP) == LEFT);
    assert(testTurn->turn(2, UP) == DOWN);
    delete testTurn;

    testTurn = new TurnBehavior(-1, 3);
    cout<<"Testing Turns (tT: -1, nC: 3)"<<endl;
    assert(testTurn->turn(0, UP) == LEFT);
    assert(testTurn->turn(1, UP) == RIGHT);
    assert(testTurn->turn(2, UP) == DOWN);
    delete testTurn;
}

void testEdgeBehavior() {
    EdgeBehavior *testEdge = new Teleport();
    auto *moveBx = new MoveBehavior();
    auto *turnBx = new TurnBehavior(1, 2);
    testEdge->setMoveBehavior(moveBx);
    testEdge->setTurnBehavior(turnBx);
    cout<<"Testing Edge Detection"<<endl;
    assert(testEdge->isEdge(std::make_pair(0, 16), UP, 1));
    assert(testEdge->isEdge(std::make_pair(10, 0), LEFT, 1));
    assert(testEdge->isEdge(std::make_pair(LEDBoard::PIXEL_ROWS - 1, 15), DOWN, 1));
    assert(testEdge->isEdge(std::make_pair(32, LEDBoard::PIXEL_COLS - 1), RIGHT, 1));

    moveBx->setMoveDistance(5);
    assert(testEdge->isEdge(std::make_pair(4, 16), UP, 1));
    assert(testEdge->isEdge(std::make_pair(LEDBoard::PIXEL_ROWS - 5, 16), DOWN, 1));
    assert(testEdge->isEdge(std::make_pair(0, 3), LEFT, 1));
    assert(testEdge->isEdge(std::make_pair(0, LEDBoard::PIXEL_COLS - 2), RIGHT, 1));

    moveBx->setMoveDistance(1);
    cout<<"---------------------- Testing Teleport --------------------------"<<endl;
    testTeleportEdgeBehavior(testEdge, moveBx);
    cout<<"---------------------- Teleport Tests Passed ---------------------"<<endl<<endl;

    testEdge = new UTurn();
    testEdge->setMoveBehavior(moveBx);
    testEdge->setTurnBehavior(turnBx);
    cout<<"---------------------- Testing UTurn -----------------------------"<<endl;
    testUTurnEdgeBehavior(testEdge, moveBx, turnBx);
    cout<<"---------------------- UTurn Tests Passed ------------------------"<<endl<<endl;

    testEdge = new Death();
    testEdge->setMoveBehavior(moveBx);
    testEdge->setTurnBehavior(turnBx);
    cout<<"---------------------- Testing Death -----------------------------"<<endl;
    testDeathEdgeBehavior(testEdge, moveBx, turnBx);
    cout<<"---------------------- Death Tests Passed ------------------------"<<endl<<endl;

    testEdge = new Wall();
    testEdge->setMoveBehavior(moveBx);
    testEdge->setTurnBehavior(turnBx);
    cout<<"---------------------- Testing Wall ------------------------------"<<endl;
    testWallEdgeBehavior(testEdge, moveBx);
    cout<<"---------------------- Wall Tests Passed -------------------------"<<endl<<endl;

    testEdge = new RandomTeleport();
    testEdge->setMoveBehavior(moveBx);
    testEdge->setTurnBehavior(turnBx);
    cout<<"---------------------- Testing RanTele ---------------------------"<<endl;
    testRandomTeleportEdgeBehavior(testEdge, moveBx);
    cout<<"---------------------- RanTele Tests Passed ----------------------"<<endl<<endl;

    delete moveBx;
    delete turnBx;
}

void testTeleportEdgeBehavior(EdgeBehavior *testEdge, MoveBehavior *moveBx) {
    std::pair<int, int> curPos(0,16);
    Direction direction = UP;

    cout<<"Testing Edge Teleports with Move Distance == 1"<<endl;
    std::pair<int, int> result = testEdge->handleEdge(curPos, direction, 0);
    assert(result.second == curPos.second && result.first == LEDBoard::PIXEL_ROWS - 1);
    result.second = LEDBoard::PIXEL_COLS;
    direction = DOWN;
    result = testEdge->handleEdge(result, direction, 0);
    assert(result.second == 0 && result.first == 0);
    direction = LEFT;
    result = testEdge->handleEdge(result, direction, 0);
    assert(result.second == LEDBoard::PIXEL_COLS - 1 && result.first == 0);
    result.first = 15;
    direction = RIGHT;
    result = testEdge->handleEdge(result, direction, 0);
    assert(result.second == 0 && result.first == 15);


    cout<<"Testing Edge Teleports with Move Distance != 1"<<endl;
    moveBx->setMoveDistance(10);
    direction = UP;
    result.first = 2;
    result.second = LEDBoard::PIXEL_COLS - 5;
    result = testEdge->handleEdge(result, direction, 0);
    assert(result.first == LEDBoard::PIXEL_ROWS - 8);
    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    result = testEdge->handleEdge(result, direction, 0);
    assert(result.second == 5);
    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    result = testEdge->handleEdge(result, direction, 0);
    assert(result.first == 2);
    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    result = testEdge->handleEdge(result, direction, 0);
    assert(result.second == LEDBoard::PIXEL_COLS - 5);

    moveBx->setMoveDistance(1);
    testEdge->setMoveBehavior(nullptr);
    testEdge->setTurnBehavior(nullptr);
    delete testEdge;
}

void testUTurnEdgeBehavior(EdgeBehavior *testEdge, MoveBehavior *moveBx, TurnBehavior *turnBx) {
    std::pair<int, int> pos = std::make_pair(0, LEDBoard::PIXEL_COLS - 1);
    Direction direction;
    int colorVal = 0;

    cout<<"Testing Edge UTurns with Move Distance == 1"<<endl;
    direction = UP;
    if(testEdge->isEdge(pos, direction)) {
        testEdge->handleEdge(pos, direction, colorVal);
        direction = turnBx->turn(colorVal, direction);
        colorVal = (colorVal + 1) & 1;
    }
    assert(direction == DOWN);

    direction = static_cast<Direction>((direction + 3) % NUM_DIRECTIONS);
    if(testEdge->isEdge(pos, direction)) {
        testEdge->handleEdge(pos, direction, colorVal);
        direction = turnBx->turn(colorVal, direction);
        colorVal = (colorVal + 1) & 1;
    }
    assert(direction == LEFT);

    pos = std::make_pair(LEDBoard::PIXEL_ROWS - 1, colorVal);
    direction = static_cast<Direction>((direction + 3) % NUM_DIRECTIONS);
    if(testEdge->isEdge(pos, direction)) {
        testEdge->handleEdge(pos, direction, colorVal);
        direction = turnBx->turn(colorVal, direction);
        colorVal = (colorVal + 1) & 1;
    }
    assert(direction == UP);

    direction = static_cast<Direction>((direction + 3) % NUM_DIRECTIONS);
    if(testEdge->isEdge(pos, direction)) {
        testEdge->handleEdge(pos, direction, colorVal);
        direction = turnBx->turn(colorVal, direction);
        colorVal = (colorVal + 1) & 1;
    }
    assert(direction == RIGHT);



    cout<<"Testing Edge UTurns with Move Distance != 1"<<endl;
    pos = std::make_pair(12, LEDBoard::PIXEL_COLS - 13);
    moveBx->setMoveDistance(15);
    direction = UP;
    if(testEdge->isEdge(pos, direction)) {
        testEdge->handleEdge(pos, direction, colorVal);
        direction = turnBx->turn(colorVal, direction);
        colorVal = (colorVal + 1) & 1;
    }
    assert(direction == DOWN);

    direction = static_cast<Direction>((direction + 3) % NUM_DIRECTIONS);
    if(testEdge->isEdge(pos, direction)) {
        testEdge->handleEdge(pos, direction, colorVal);
        direction = turnBx->turn(colorVal, direction);
        colorVal = (colorVal + 1) & 1;
    }
    assert(direction == LEFT);

    pos = std::make_pair(LEDBoard::PIXEL_ROWS - 10, 10);
    direction = static_cast<Direction>((direction + 3) % NUM_DIRECTIONS);
    if(testEdge->isEdge(pos, direction)) {
        testEdge->handleEdge(pos, direction, colorVal);
        direction = turnBx->turn(colorVal, direction);
        colorVal = (colorVal + 1) & 1;
    }
    assert(direction == UP);

    direction = static_cast<Direction>((direction + 3) % NUM_DIRECTIONS);
    if(testEdge->isEdge(pos, direction)) {
        testEdge->handleEdge(pos, direction, colorVal);
        direction = turnBx->turn(colorVal, direction);
        colorVal = (colorVal + 1) & 1;
    }
    assert(direction == RIGHT);

    moveBx->setMoveDistance(1);
    testEdge->setMoveBehavior(nullptr);
    testEdge->setTurnBehavior(nullptr);
    delete testEdge;
}

void testWallEdgeBehavior(EdgeBehavior *testEdge, MoveBehavior *moveBx) {
    std::pair<int, int> pos = std::make_pair(0, 15);
    Direction direction;

    cout<<"Testing Edge Walls with Move Distance == 1"<<endl;
    direction = UP;
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(direction == UP);

    direction = RIGHT;
    pos = std::make_pair(15, LEDBoard::PIXEL_COLS - 1);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(direction == RIGHT);

    direction = DOWN;
    pos = std::make_pair(LEDBoard::PIXEL_ROWS - 1, 15);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(direction == DOWN);

    direction = LEFT;
    pos = std::make_pair(15, 0);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(direction == LEFT);

    cout<<"Testing Edge Walls with Move Distance != 1"<<endl;
    direction = UP;
    moveBx->setMoveDistance(15);
    pos = std::make_pair(10, 10);
    if(testEdge->isEdge(pos, direction))
        pos = testEdge->handleEdge(pos, direction, 0);
    assert(direction == UP);
    assert(pos.first == 0);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(direction == UP);

    direction = RIGHT;
    pos = std::make_pair(20, 20);
    if(testEdge->isEdge(pos, direction))
        pos = testEdge->handleEdge(pos, direction, 0);
    assert(direction == RIGHT);
    assert(pos.second == LEDBoard::PIXEL_COLS - 1);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(direction == RIGHT);

    direction = DOWN;
    pos = std::make_pair(20, 20);
    if(testEdge->isEdge(pos, direction))
        pos = testEdge->handleEdge(pos, direction, 0);
    assert(direction == DOWN);
    assert(pos.first == LEDBoard::PIXEL_ROWS - 1);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(direction == DOWN);

    direction = LEFT;
    pos = std::make_pair(10, 10);
    if(testEdge->isEdge(pos, direction))
        pos = testEdge->handleEdge(pos, direction, 0);
    assert(direction == LEFT);
    assert(pos.second == 0);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(direction == LEFT);

    cout<<"Testing Corner Walls"<<endl;
    direction = UP;
    moveBx->setMoveDistance(1);
    pos = std::make_pair(0, LEDBoard::PIXEL_COLS - 1);
    if(testEdge->isEdge(pos, direction))
        pos = testEdge->handleEdge(pos, direction, 0);
    assert(direction == RIGHT);

    pos = std::make_pair(LEDBoard::PIXEL_ROWS - 1, LEDBoard::PIXEL_COLS - 1);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(direction == DOWN);

    pos = std::make_pair(LEDBoard::PIXEL_ROWS - 1, 0);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(direction == LEFT);

    pos = std::make_pair(0, 0);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(direction == UP);

    moveBx->setMoveDistance(1);
    testEdge->setMoveBehavior(nullptr);
    testEdge->setTurnBehavior(nullptr);
    delete testEdge;
}

void testDeathEdgeBehavior(EdgeBehavior *testEdge, MoveBehavior *moveBx, TurnBehavior *turnBx) {
    std::pair<int, int> pos = std::make_pair(0, LEDBoard::PIXEL_COLS - 1);
    Direction direction;

    cout<<"Testing Edge Deaths with Move Distance == 1"<<endl;
    direction = UP;
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(moveBx->getMoveDistance() == 0);

    moveBx->setMoveDistance(1);
    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(moveBx->getMoveDistance() == 0);

    moveBx->setMoveDistance(1);
    pos = std::make_pair(LEDBoard::PIXEL_ROWS - 1, 0);
    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(moveBx->getMoveDistance() == 0);

    moveBx->setMoveDistance(1);
    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(moveBx->getMoveDistance() == 0);


    cout<<"Testing Edge Deaths with Move Distance != 1"<<endl;
    pos = std::make_pair(10, LEDBoard::PIXEL_COLS - 12);
    moveBx->setMoveDistance(15);
    direction = UP;
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(moveBx->getMoveDistance() == 0);

    moveBx->setMoveDistance(15);
    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(moveBx->getMoveDistance() == 0);

    pos = std::make_pair(LEDBoard::PIXEL_ROWS - 13, 12);
    moveBx->setMoveDistance(15);
    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    if(testEdge->isEdge(pos, direction))
        testEdge->handleEdge(pos, direction, 0);
    assert(moveBx->getMoveDistance() == 0);

    moveBx->setMoveDistance(15);
    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    if(testEdge->isEdge(pos, direction))
        pos = testEdge->handleEdge(pos, direction, 0);
    assert(moveBx->getMoveDistance() == 0);
    assert(pos != REMOVE_ANT_SIGNAL);

    testEdge->setTurnBehavior(nullptr);
    testEdge->setMoveBehavior(nullptr);
    delete testEdge;
    testEdge = new Death(true);
    testEdge->setTurnBehavior(turnBx);
    testEdge->setMoveBehavior(moveBx);

    cout<<"Testing Edge Deaths with Removal"<<endl;
    pos = std::make_pair(0, LEDBoard::PIXEL_COLS - 1);
    moveBx->setMoveDistance(1);
    direction = UP;
    pos = testEdge->handleEdge(pos, direction, 0);
    assert(pos == REMOVE_ANT_SIGNAL);

    pos = std::make_pair(0, LEDBoard::PIXEL_COLS - 1);
    moveBx->setMoveDistance(1);
    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    pos = testEdge->handleEdge(pos, direction, 0);
    assert(pos == REMOVE_ANT_SIGNAL);

    pos = std::make_pair(LEDBoard::PIXEL_ROWS - 1, 0);
    moveBx->setMoveDistance(1);
    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    pos = testEdge->handleEdge(pos, direction, 0);
    assert(pos == REMOVE_ANT_SIGNAL);

    pos = std::make_pair(LEDBoard::PIXEL_ROWS - 1, 0);
    moveBx->setMoveDistance(1);
    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    pos = testEdge->handleEdge(pos, direction, 0);
    assert(pos == REMOVE_ANT_SIGNAL);

    moveBx->setMoveDistance(1);
    testEdge->setMoveBehavior(nullptr);
    testEdge->setTurnBehavior(nullptr);
    delete testEdge;
}

void testRandomTeleportEdgeBehavior(EdgeBehavior *testEdge, MoveBehavior *moveBx) {
    std::pair<int, int> pos;
    Direction direction;
    int totalR, totalC, numTries = 100;

    cout<<"Testing Edge RanTele with Move Distance == 1"<<endl;
    direction = UP;
    totalR = 0;
    totalC = 0;
    for (int i = 0; i < numTries; ++i) {
        pos = std::make_pair(0,10);
        pos = testEdge->handleEdge(pos, direction, 0);
        totalR += pos.first;
        totalC += pos.second;
    }
    assert(totalC / numTries < LEDBoard::PIXEL_COLS && totalC / numTries > 0);
    assert(totalR / numTries < LEDBoard::PIXEL_COLS && totalR / numTries > 0);

    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    totalR = 0;
    totalC = 0;
    for (int i = 0; i < numTries; ++i) {
        pos = std::make_pair(15, LEDBoard::PIXEL_COLS - 1);
        pos = testEdge->handleEdge(pos, direction, 0);
        totalR += pos.first;
        totalC += pos.second;
    }
    assert(totalC / numTries < LEDBoard::PIXEL_COLS && totalC / numTries > 0);
    assert(totalR / numTries < LEDBoard::PIXEL_COLS && totalR / numTries > 0);

    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    totalR = 0;
    totalC = 0;
    for (int i = 0; i < numTries; ++i) {
        pos = std::make_pair(LEDBoard::PIXEL_ROWS - 1,10);
        pos = testEdge->handleEdge(pos, direction, 0);
        totalR += pos.first;
        totalC += pos.second;
    }
    assert(totalC / numTries < LEDBoard::PIXEL_COLS && totalC / numTries > 0);
    assert(totalR / numTries < LEDBoard::PIXEL_COLS && totalR / numTries > 0);

    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    totalR = 0;
    totalC = 0;
    for (int i = 0; i < numTries; ++i) {
        pos = std::make_pair(15,0);
        pos = testEdge->handleEdge(pos, direction, 0);
        totalR += pos.first;
        totalC += pos.second;
    }
    assert(totalC / numTries < LEDBoard::PIXEL_COLS && totalC / numTries > 0);
    assert(totalR / numTries < LEDBoard::PIXEL_COLS && totalR / numTries > 0);

    moveBx->setMoveDistance(15);
    cout<<"Testing Edge RanTele with Move Distance != 1"<<endl;
    direction = UP;
    totalR = 0;
    totalC = 0;
    for (int i = 0; i < numTries; ++i) {
        pos = std::make_pair(10,10);
        pos = testEdge->handleEdge(pos, direction, 0);
        totalR += pos.first;
        totalC += pos.second;
    }
    assert(totalC / numTries < LEDBoard::PIXEL_COLS && totalC / numTries > 0);
    assert(totalR / numTries < LEDBoard::PIXEL_COLS && totalR / numTries > 0);

    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    totalR = 0;
    totalC = 0;
    for (int i = 0; i < numTries; ++i) {
        pos = std::make_pair(LEDBoard::PIXEL_ROWS - 13,LEDBoard::PIXEL_COLS - 8);
        pos = testEdge->handleEdge(pos, direction, 0);
        totalR += pos.first;
        totalC += pos.second;
    }
    assert(totalC / numTries < LEDBoard::PIXEL_COLS && totalC / numTries > 0);
    assert(totalR / numTries < LEDBoard::PIXEL_COLS && totalR / numTries > 0);

    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    totalR = 0;
    totalC = 0;
    for (int i = 0; i < numTries; ++i) {
        pos = std::make_pair(LEDBoard::PIXEL_ROWS - 13,LEDBoard::PIXEL_COLS - 8);
        pos = testEdge->handleEdge(pos, direction, 0);
        totalR += pos.first;
        totalC += pos.second;
    }
    assert(totalC / numTries < LEDBoard::PIXEL_COLS && totalC / numTries > 0);
    assert(totalR / numTries < LEDBoard::PIXEL_COLS && totalR / numTries > 0);

    direction = static_cast<Direction>((direction + 1) % NUM_DIRECTIONS);
    totalR = 0;
    totalC = 0;
    for (int i = 0; i < numTries; ++i) {
        pos = std::make_pair(10,10);
        pos = testEdge->handleEdge(pos, direction, 0);
        totalR += pos.first;
        totalC += pos.second;
    }
    assert(totalC / numTries < LEDBoard::PIXEL_COLS && totalC / numTries > 0);
    assert(totalR / numTries < LEDBoard::PIXEL_COLS && totalR / numTries > 0);

    moveBx->setMoveDistance(1);
    testEdge->setMoveBehavior(nullptr);
    testEdge->setTurnBehavior(nullptr);
    delete testEdge;
}