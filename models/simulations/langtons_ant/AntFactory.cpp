/****************************************************************************************
 *
 ***************************************************************************************/
#include "AntFactory.hpp"
AntFactory* AntFactory::antFactory = nullptr;

AntFactory::AntFactory() {
    bxFactory = BehaviorFactory::getInstance();
    antDefaults = AntDataService::getInstance();
}

AntFactory::~AntFactory() {
    bxFactory = nullptr;
    antFactory = nullptr;
}

AntFactory *AntFactory::getInstance() {
    if (antFactory == nullptr) {
        antFactory = new AntFactory();
    }
    return antFactory;
}

Ant *AntFactory::makeAnt(int size) {
    std::pair<int, int> pos = std::make_pair(getRandomPosValue(LEDBoard::PIXEL_ROWS - size),
                                             getRandomPosValue(LEDBoard::PIXEL_COLS - size));
    Behaviors bx = bxFactory->createBehaviors();
    if (size > 1) {
        return new BigAnt(size, pos, UP, bx, antDefaults->getDefaultColor());
    } else {
        return new Ant(pos, UP, bx, antDefaults->getDefaultColor());
    }
}

int AntFactory::getRandomPosValue(int upperBound) {
    std::uniform_int_distribution<int> range(0, upperBound);

    return range(randGen);
}
