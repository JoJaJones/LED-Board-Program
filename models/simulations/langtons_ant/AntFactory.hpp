/****************************************************************************************
 *
 ***************************************************************************************/
#ifndef LED_BOARD_PROGRAM_ANTFACTORY_HPP
#define LED_BOARD_PROGRAM_ANTFACTORY_HPP

#include "BehaviorFactory.hpp"
#include "BigAnt.hpp"
#include <random>


class AntFactory {
private:
    static AntFactory *antFactory;
    std::default_random_engine randGen;

    AntDataService *antDefaults;
    BehaviorFactory *bxFactory;
    AntFactory();
    int getRandomPosValue(int upperBound);
public:
    ~AntFactory();
    static AntFactory* getInstance();
    Ant* makeAnt(int size = 1);
};

#endif //LED_BOARD_PROGRAM_ANTFACTORY_HPP
