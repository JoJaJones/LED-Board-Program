//
// Created by theom on 10/6/2020.
//
#include <iostream>
#include <simulations/langtons_ant/MoveBehavior.hpp>
#include <cassert>
#include <vector>
#include <simulations/langtons_ant/TurnBehavior.hpp>

void testMoveBehavior();
void testTurnBehavior();
void testEdgeBehavior();
void testTeleportEdgeBehavior();
void testUTurnEdgeBehavior();
void testWallEdgeBehavior();
void testDeathEdgeBehavior();
void testRandomTeleportEdgeBehavior();

using std::cout;
using std::endl;

int main(){
    cout<<"********************** Testing Move Behavior *********************"<<endl;
    testMoveBehavior();
    cout<<"******************* Move Behavior Tests Passed *******************"<<endl<<endl;

    cout<<"********************** Testing Turn Behavior *********************"<<endl;
    testTurnBehavior();
    cout<<"******************* Turn Behavior Tests Passed *******************"<<endl<<endl;

    cout<<"********************** Testing Edge Behavior *********************"<<endl;

    cout<<"******************* Edge Behavior Tests Passed *******************"<<endl<<endl;
    return 0;
}

void testMoveBehavior() {
    MoveBehavior testMove(1);
    std::pair<int, int> posStart(5,5);
    std::pair<int, int> posResult;

    posResult = testMove.move(posStart, UP);
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