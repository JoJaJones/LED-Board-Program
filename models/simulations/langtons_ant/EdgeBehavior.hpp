/******************************************************************************
 * This hpp declares a set oc classes to determine how hitting the edge of the
 * board is handled in this highly customizable langton's ant implementation
 *****************************************************************************/

#ifndef LED_BOARD_PROGRAM_EDGEBEHAVIOR_HPP
#define LED_BOARD_PROGRAM_EDGEBEHAVIOR_HPP


#include "TurnBehavior.hpp"
#include "MoveBehavior.hpp"
#include <board_constants.hpp>
#include <algorithm>
#include <random>

// enum for behavior type selection in files that reference this set of classes
enum EdgeType {
    WALL,
    TELEPORT,
    DEATH,
    REMOVE,
    UTURN,
    RANDOM_TELEPORT
};

/******************************************************************************
 * EdgeBehavior interface that all concrete behavior classes will implement
 *****************************************************************************/
class EdgeBehavior {
protected:
    // since some behaviors need access to move and/or turn behavior these pointers
    // are to reference the move and turn behavior specific to the ant
    MoveBehavior *moveBehavior;
    TurnBehavior *turnBehavior;
    std::pair<int, int> adjustPos(std::pair<int, int> nextPos);
    virtual std::pair<int, int> adjustPos(std::pair<int, int> nextPos, int size);
public:
    EdgeBehavior();
    EdgeBehavior(MoveBehavior *moveBx);
    EdgeBehavior(TurnBehavior *turnBx);
    EdgeBehavior(MoveBehavior *moveBx, TurnBehavior *turnBx);
    virtual ~EdgeBehavior() = default;
    bool isEdge(std::pair<int, int> curPos, Direction direction, int size = 1);
    bool isOnEdge(std::pair<int, int> curPos, Direction direction, int size = 1);
    virtual std::pair<int, int> handleEdge(std::pair<int, int> curPos,
                                           Direction &direction, int colorVal);
    virtual std::pair<int, int> handleEdge(std::pair<int, int> curPos,
                                           Direction &direction, int colorVal, int size) = 0;
    std::vector<std::pair<int, int>> adjustPositions(std::vector<std::pair<int, int>> &nextPos);
    void setMoveBehavior(MoveBehavior *moveBx);
    void setTurnBehavior(TurnBehavior *turnBx);
};

/******************************************************************************
 * Implementation of the EdgeBehavior interface to cause teleportation to the
 * opposite side of the board upon crossing the edge of the board
 *****************************************************************************/
class Teleport : public EdgeBehavior {
private:
    std::pair<int, int> adjustPos(std::pair<int, int> nextPos, int size) override;
public:
    Teleport();
    Teleport(MoveBehavior *moveBx);
    Teleport(TurnBehavior *turnBx);
    Teleport(MoveBehavior *moveBx, TurnBehavior *turnBx);
    std::pair<int, int> handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal, int size) override;
};

/******************************************************************************
 * Implementation of the EdgeBehavior interface to provide U-turn response
 * to interactions with the edge of the board
 *****************************************************************************/
class UTurn : public EdgeBehavior {
public:
    UTurn();
    UTurn(MoveBehavior *moveBx);
    UTurn(TurnBehavior *turnBx);
    UTurn(MoveBehavior *moveBx, TurnBehavior *turnBx);
    std::pair<int, int> handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal, int size) override;
};

/******************************************************************************
 * Implementation of the EdgeBehavior interface to provide Ant death behaviors
 * upon interation with the edge of the board
 *****************************************************************************/
class Death : public EdgeBehavior {
private:
    bool removeOnDeath;

public:
    explicit Death(bool remove = false);
    Death(MoveBehavior *moveBx, bool remove = false);
    Death(TurnBehavior *turnBx, bool remove = false);
    Death(MoveBehavior *moveBx, TurnBehavior *turnBx, bool remove = false);
    std::pair<int, int> handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal, int size) override;
};

/******************************************************************************
 * Implementation of the EdgeBehavior interface to provide a simulated
 * barrier at the border of the board.
 *****************************************************************************/
class Wall : public EdgeBehavior {
public:
    Wall();
    Wall(MoveBehavior *moveBx);
    Wall(TurnBehavior *turnBx);
    Wall(MoveBehavior *moveBx, TurnBehavior *turnBx);
    std::pair<int, int> handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal, int size) override;
};

/******************************************************************************
 * Implementation of the EdgeBehavior interface to teleportation to a random
 * location on the board upon interaction with the edge of the board.
 *****************************************************************************/
class RandomTeleport : public EdgeBehavior {
private:
    std::default_random_engine randGen;
    std::uniform_int_distribution<int> rowRange;
    std::uniform_int_distribution<int> colRange;

public:
    explicit RandomTeleport(int antSize = 1);
    RandomTeleport(MoveBehavior *moveBx, int antSize = 1);
    RandomTeleport(TurnBehavior *turnBx, int antSize = 1);
    RandomTeleport(MoveBehavior *moveBx, TurnBehavior *turnBx, int antSize = 1);
    std::pair<int, int> handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal, int size) override;
};

/******************************************************************************
 * Struct to contain all behavior strategies to reduce parameters needed to
 * initialize Ant objects
 *****************************************************************************/
struct Behaviors {
    EdgeBehavior *edgeBx;
    MoveBehavior *moveBX;
    TurnBehavior *turnBx;
};
#endif //LED_BOARD_PROGRAM_EDGEBEHAVIOR_HPP
