/****************************************************************************************
 *
 ***************************************************************************************/
#ifndef LED_BOARD_PROGRAM_ANTPOSITION_HPP
#define LED_BOARD_PROGRAM_ANTPOSITION_HPP

#include <Position.hpp>
#include "Ant.hpp"
#include <vector>
#include <constants.hpp>


class AntPosition : public LEDBoard::Position<std::vector<Ant*>> {
private:
    std::vector<Ant*> deadAnts;
    std::vector<Ant*> newAnts;

public:
    AntPosition();

};


#endif //LED_BOARD_PROGRAM_ANTPOSITION_HPP
