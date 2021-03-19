/****************************************************************************************
 * Implementation for the associated header to create a highly customizable ant in the
 * Langton's Ant simulation
 ***************************************************************************************/
#include "Ant.hpp"

// Constructors
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

// destructor
Ant::~Ant() {
    delete turnBx;
    delete moveBx;
    delete edgeBx;
}

/****************************************************************************************
 * Function to sanitize chosen setttings to ensure that the ant is placed correctly on
 * the board
 ***************************************************************************************/
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

// helper functions to actually sanitize the value
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

/****************************************************************************************
 * Function to implement the movement behavior of the ant
 *
 * @param color: integer valur indicating the index of the color of the current position
 * @return: pointer to the current Ant object so it can be relocated to a new position
 ***************************************************************************************/
Ant *Ant::move_ant(int color) {
    // if the move would carry the ant over the edge perform the relevant edge action
    if (edgeBx->isEdge(pos, heading, 1)){
        pos = edgeBx->handleEdge(pos, heading, color);
    } else {
        pos = moveBx->move(pos, heading);
    }

    return this;
}

/****************************************************************************************
 * Function to detect if the ant is dead
 *
 * @return: boolean value indicating whether the ant is dead or not
 ***************************************************************************************/
bool Ant::isDead() {
    return moveBx == nullptr || moveBx->getMoveDistance() == 0;
}

/****************************************************************************************
 * Function to change the current direction of the ant
 *
 * @param color: integer valur indicating the index of the color of the current position
 ***************************************************************************************/
void Ant::changeDirection(int color) {
    heading = turnBx->turn(color, heading);
}

/****************************************************************************************
 * Function to return a vector of positions the ant currently occupies (vector used to
 * allow for compatibility with the BigAnt special option)
 *
 * @return: a vector of positions occupied by the and
 ***************************************************************************************/
std::vector<std::pair<int, int>> * Ant::getPos() {
    return new std::vector<std::pair<int, int>>(1, pos);
}

/****************************************************************************************
 * Set function to modify the edge behavior of the ant
 ***************************************************************************************/
void Ant::setEdgeBx(EdgeBehavior *edgeBehavior) {
    edgeBx = edgeBehavior;
}

/****************************************************************************************
 * Set function to modify the turn behavior of the current ant
 ***************************************************************************************/
void Ant::setTurnBehavior(TurnBehavior *turnBehavior) {
    turnBx = turnBehavior;
}

/****************************************************************************************
 * Set function to modify the move behavior of the current ant
 ***************************************************************************************/
void Ant::setMoveDistance(int distance) {
    moveBx->setMoveDistance(distance);
}
