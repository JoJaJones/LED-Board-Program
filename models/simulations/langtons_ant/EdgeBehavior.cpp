#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
/***********************************************************************************************************************
 * This cpp provides the necessary implmentaions for the classes and methods declared in the associated header file
 * in order to provide functionality related to behavior of the simulated Ants upon interacting with the edge of the
 * board.
 **********************************************************************************************************************/

#include "EdgeBehavior.hpp"

// Constructors for EdgeBehaviors **************************************************************************************
EdgeBehavior::EdgeBehavior()
            : EdgeBehavior(nullptr, nullptr) {}

EdgeBehavior::EdgeBehavior(MoveBehavior *moveBx)
            : EdgeBehavior(moveBx, nullptr){}

EdgeBehavior::EdgeBehavior(TurnBehavior *turnBx)
            : EdgeBehavior(nullptr, turnBx){}

EdgeBehavior::EdgeBehavior(MoveBehavior *moveBx, TurnBehavior *turnBx)
            : turnBehavior(turnBx),
              moveBehavior(moveBx) {}

RandomTeleport::RandomTeleport(int antSize)
              : rowRange(0, LEDBoard::PIXEL_ROWS - antSize),
                colRange(0, LEDBoard::PIXEL_COLS - antSize) {}

RandomTeleport::RandomTeleport(MoveBehavior *moveBx, int antSize)
              : EdgeBehavior(moveBx),
                rowRange(0, LEDBoard::PIXEL_ROWS - antSize),
                colRange(0, LEDBoard::PIXEL_COLS - antSize){}

RandomTeleport::RandomTeleport(TurnBehavior *turnBx, int antSize)
              : EdgeBehavior(turnBx),
                rowRange(0, LEDBoard::PIXEL_ROWS - antSize),
                colRange(0, LEDBoard::PIXEL_COLS - antSize){}

RandomTeleport::RandomTeleport(MoveBehavior *moveBx, TurnBehavior *turnBx, int antSize)
              : EdgeBehavior(moveBx, turnBx),
                rowRange(0, LEDBoard::PIXEL_ROWS - antSize),
                colRange(0, LEDBoard::PIXEL_COLS - antSize){}

Death::Death(bool remove)
     : removeOnDeath(remove) {}

Death::Death(MoveBehavior *moveBx, bool remove)
     : EdgeBehavior(moveBx),
       removeOnDeath(remove) {}

Death::Death(TurnBehavior *turnBx, bool remove)
     : EdgeBehavior(turnBx),
       removeOnDeath(remove) {}

Death::Death(MoveBehavior *moveBx, TurnBehavior *turnBx, bool remove)
     : EdgeBehavior(moveBx, turnBx),
       removeOnDeath(remove) {}

Teleport::Teleport()
        : EdgeBehavior() {}

Teleport::Teleport(MoveBehavior *moveBx)
        : EdgeBehavior(moveBx) {}

Teleport::Teleport(TurnBehavior *turnBx)
        : EdgeBehavior(turnBx) {}

Teleport::Teleport(MoveBehavior *moveBx, TurnBehavior *turnBx)
        : EdgeBehavior(moveBx, turnBx) {}

UTurn::UTurn()
     : EdgeBehavior() {}

UTurn::UTurn(MoveBehavior *moveBx)
     : EdgeBehavior(moveBx) {}

UTurn::UTurn(TurnBehavior *turnBx)
     : EdgeBehavior(turnBx) {}

UTurn::UTurn(MoveBehavior *moveBx, TurnBehavior *turnBx)
     : EdgeBehavior(moveBx, turnBx) {}

Wall::Wall()
    : EdgeBehavior() {}

Wall::Wall(MoveBehavior *moveBx)
    : EdgeBehavior(moveBx) {}

Wall::Wall(TurnBehavior *turnBx)
    : EdgeBehavior(turnBx) {}

Wall::Wall(MoveBehavior *moveBx, TurnBehavior *turnBx)
    : EdgeBehavior(moveBx, turnBx) {}
// End Constructors ****************************************************************************************************

// Set Functions *******************************************************************************************************
void EdgeBehavior::setMoveBehavior(MoveBehavior *moveBx) {
    this->moveBehavior = moveBx;
}

void EdgeBehavior::setTurnBehavior(TurnBehavior *turnBx) {
    this->turnBehavior = turnBx;
}
// End Set Functions ***************************************************************************************************

/***********************************************************************************************************************
 * Function to correct edge position for edge behaviors that do not result in teleportation in order to account for
 * movement speeds larger than 1
 *
 * @param nextPos: pair containing the calculated next position of the top left pixel of the Ant object in row, col
 *                 format
 * @param size: int containing the size of the ant
 * @return pair containing corrected next position of the Ant object's top left pixel
 **********************************************************************************************************************/
std::pair<int, int> EdgeBehavior::adjustPos(std::pair<int, int> nextPos, int size) {
    if(nextPos.first < 0){
        nextPos.first = 0;
    } else if (nextPos.first > LEDBoard::PIXEL_ROWS - size){
        nextPos.first = LEDBoard::PIXEL_ROWS - 1;
    }

    if(nextPos.second < 0){
        nextPos.second = 0;
    } else if (nextPos.second > LEDBoard::PIXEL_COLS - size) {
        nextPos.second = LEDBoard::PIXEL_COLS - 1;
    }

    return nextPos;
}

/***********************************************************************************************************************
 * Function to detect if the ant is on the edge of the board to detect the need for certain types of edge behavior. This
 * function will differentiate between moves that will cross the edge from moves that start at the edge for move
 * distances greater than 1
 *
 * @param curPos: Ant object's current position on the board in row, col format
 * @param direction: Ant object's current direction
 * @param size: size of the Ant object
 * @return boolean value indicating whether the Ant object is on the edge of the board
 **********************************************************************************************************************/
bool EdgeBehavior::isOnEdge(std::pair<int, int> curPos, Direction direction, int size) {
    std::pair<int, int> nextPos = moveBehavior->move(curPos, direction, 1);
    if (std::min(nextPos.first, nextPos.second) < 0) {
        return true;
    }

    if (nextPos.first > LEDBoard::PIXEL_ROWS - size || nextPos.second > LEDBoard::PIXEL_COLS - size){
        return true;
    }

    return false;
}

/***********************************************************************************************************************
 * Function to detect if the move will cross an edge so that the proper edge handling can be performed
 *
 * @param curPos: Ant object's current position on the board  in row, col format
 * @param direction: Ant object's current direction
 * @param size: size of the Ant object
 * @return boolean value indicating whether the Ant object will cross the edge with its next move
 **********************************************************************************************************************/
bool EdgeBehavior::isEdge(std::pair<int, int> curPos, Direction direction, int size) {
    std::pair<int, int> nextPos = moveBehavior->move(curPos, direction);
    if(nextPos.first < 0 || nextPos.second < 0){
        return true;
    }

    if(nextPos.first > LEDBoard::PIXEL_ROWS - size || nextPos.second > LEDBoard::PIXEL_COLS - size){
        return true;
    }

    return false;
}

/***********************************************************************************************************************
 * Function overload to allow for calling handleEdge without passing a size value for Ant objects that are not BigAnts.
 * It calls handleEdge with a size of 1 since any ant without a size value will be of size 1
 *
 * @param curPos: Current position of the Ant  in row, col format
 * @param direction: Current heading of the Ant
 * @param colorVal: Color index of the color of the current position (only used in wall and UTurn)
 * @return a pair containing the next position of the Ant object in row, col format
 **********************************************************************************************************************/
std::pair<int, int> EdgeBehavior::handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal) {
    return handleEdge(curPos, direction, colorVal, 1);
}

/***********************************************************************************************************************
 * Function to adjust the positions of BigAnts if they cross the edge of the board. Since BigAnt position data is saved
 * as only the position of the top left pixel and all others must be derived from that information, for Teleport Edge
 * behavior it's possible for part of the ant to extend beyond one or more edge of the board and this function corrects
 * those pieces
 *
 * @param nextPos: reference to vector of pairs containing the positions the ant occupies in row, col format
 * @return vector passed into the function after its modification
 **********************************************************************************************************************/
std::vector<std::pair<int, int>> EdgeBehavior::adjustPositions(std::vector<std::pair<int, int>> &nextPos) {
    for(auto &pos : nextPos){
        pos = adjustPos(pos);
    }

    return nextPos;
}
/***********************************************************************************************************************
 * Function overload to allow for calling adjustPos without passing a size value for Ant objects that are not BigAnts.
 * It calls adjustPos with a size of 1 since any ant without a size value will be of size 1
 *
 * @param nextPos: pair containing the position to be adjusted in row, col format
 * @return pair with the adjusted position value in row, col format
 **********************************************************************************************************************/
std::pair<int, int> EdgeBehavior::adjustPos(std::pair<int, int> nextPos) {
   return adjustPos(nextPos, 1);
}

/***********************************************************************************************************************
 * Function to teleport the Ant object to the opposite side of the board when it crosses the edge
 *
 * @param curPos: Current position of the Ant  in row, col format
 * @param direction: Current heading of the Ant
 * @param colorVal: Color index of the color of the current position (only used in wall and UTurn)
 * @param size: size of the Ant object in pixels per side
 * @return a pair containing the next position of the Ant object in row, col format
 **********************************************************************************************************************/
std::pair<int, int> Teleport::handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal, int size) {
    return EdgeBehavior::adjustPos(moveBehavior->move(curPos, direction));;
}

/***********************************************************************************************************************
 * Override of EdgeBehavior adjustPos to adjust the position by teleporting instead of stopping movement
 *
 * @param nextPos: position to be adjusted in row, col format
 * @param size: size of the ant (unneeded for this function but necessary for the override)
 * @return position after teleporting the ant across the board in row, col format
 **********************************************************************************************************************/
std::pair<int, int> Teleport::adjustPos(std::pair<int, int> nextPos, int size) {
    nextPos.first += LEDBoard::PIXEL_ROWS;
    nextPos.first %= LEDBoard::PIXEL_ROWS;

    nextPos.second += LEDBoard::PIXEL_COLS;
    nextPos.second %= LEDBoard::PIXEL_COLS;

    return nextPos;
}

/***********************************************************************************************************************
 * Function to cause the ant to perform a U-turn when it attempts to cross the edge of the board
 *
 * @param curPos: Current position of the Ant  in row, col format
 * @param direction: reference to current heading of the Ant
 * @param colorVal: Color index of the color of the current position (only used in wall and UTurn)
 * @param size: size of the Ant object in pixels per side
 * @return a pair containing the next position of the Ant object in row, col format
 **********************************************************************************************************************/
std::pair<int, int> UTurn::handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal, int size) {
    std::pair<int, int> nextPos = adjustPos(moveBehavior->move(curPos, direction), size);
    Direction targetDir, tempDir = turnBehavior->turn(colorVal, direction);
    targetDir = static_cast<Direction>((direction + NUM_DIRECTIONS / 2) % NUM_DIRECTIONS);

    // since the last stem of movement is turning it will occur after handling the edge so turn 1 less time than
    // necessary to perform a U-turn
    while(tempDir != targetDir) {
        direction = tempDir;
        tempDir = turnBehavior->turn(colorVal, tempDir);
    }

    return nextPos;
}

/***********************************************************************************************************************
 * Function to handle death of the Ant upon attempting to cross the borders of the board. If the ant is not to be
 * removed upon death the move distance is set to 0 otherwise the Ant's position is returned as (-1, -1) as a signal
 * value
 *
 * @param curPos: Current position of the Ant  in row, col format
 * @param direction: Current heading of the Ant
 * @param colorVal: Color index of the color of the current position (only used in wall and UTurn)
 * @param size: size of the Ant object in pixels per side
 * @return a pair containing the next position of the Ant object in row, col format
 **********************************************************************************************************************/
std::pair<int, int> Death::handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal, int size) {
    std::pair<int, int> nextPos = adjustPos(moveBehavior->move(curPos, direction), size);

    // set nextPos to invalid Position value
    if(removeOnDeath){
        nextPos = REMOVE_ANT_SIGNAL;
    }

    moveBehavior->setMoveDistance();

    return nextPos;
}

/***********************************************************************************************************************
 * Function to handle wall edge behavior. It stops the ant at the edge of the board if it tries to cross and if the Ant
 * would end up in the corner performs turns to prevent the Ant getting stuck in place.
 *
 * @param curPos: Current position of the Ant  in row, col format
 * @param direction: Current heading of the Ant
 * @param colorVal: Color index of the color of the current position (only used in wall and UTurn)
 * @param size: size of the Ant object in pixels per side
 * @return a pair containing the next position of the Ant object in row, col format
 **********************************************************************************************************************/
std::pair<int, int> Wall::handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal, int size) {
    std::pair<int, int> nextPos;

    // if ant not at the edge move there first (since we won't know the color of the edge position until we get there)
    if(std::min(curPos.first, curPos.second) - 1 >= 0 && curPos.first + 1 <= LEDBoard::PIXEL_ROWS - size
            && curPos.second + 1 <= LEDBoard::PIXEL_COLS - size) {
        nextPos = adjustPos(moveBehavior->move(curPos, direction), size);
    } else { //ant is already on edge
        nextPos = curPos;
        Direction tempDir = direction;

        // while loop to prevent getting stuck in the corners
        while (isOnEdge(curPos, tempDir, 1)) {
            direction = tempDir;
            tempDir = turnBehavior->turn(colorVal, direction);
        }
    }
    return nextPos;
}

/***********************************************************************************************************************
 * Function to handle random teleportation upon any piece of the ant crossing the edge of the board.
 *
 * @param curPos: Current position of the Ant  in row, col format
 * @param direction: Current heading of the Ant
 * @param colorVal: Color index of the color of the current position (only used in wall and UTurn)
 * @param size: size of the Ant object in pixels per side
 * @return a pair containing the next position of the Ant object in row, col format
 **********************************************************************************************************************/
std::pair<int, int> RandomTeleport::handleEdge(std::pair<int, int> curPos, Direction &direction, int colorVal, int size) {
    return std::make_pair(rowRange(randGen), colRange(randGen));
}



#pragma clang diagnostic pop