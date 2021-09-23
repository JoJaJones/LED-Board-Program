/****************************************************************************************
 *
 ***************************************************************************************/
#include "AntPosition.hpp"

bool AntPosition::hasDeadAnts() {
    return deadAnts.size() > 0;
}

bool AntPosition::isOccupied() {
    return occupants.size() > 0;
}

std::vector<Ant *> * AntPosition::getOccupants() {
    return &occupants;
}

int AntPosition::getColor() {
    if (isOccupied()){
        return occupants[0]->getColor();
    } else if (hasDeadAnts()) {
        return deadAnts[0]->getColor();
    } else {
        return this->color;
    }
}