/****************************************************************************************
 *
 ***************************************************************************************/
#ifndef LED_BOARD_PROGRAM_BIGANT_HPP
#define LED_BOARD_PROGRAM_BIGANT_HPP

#include "Ant.hpp"

class BigAnt : public Ant {
private:
    int size;
    int hasMovedThisStep;

public:
    BigAnt(int size, std::pair<int,int> pos, Direction dir, Behaviors bx, LEDBoard::Colors color);
    BigAnt(int size, std::pair<int,int> pos, Direction dir, MoveBehavior *move,
            TurnBehavior *turn, EdgeBehavior *edge, LEDBoard::Colors color);
    Ant *move_ant(int color) override;

    std::vector<std::pair<int, int>> *getPos() override;
};


#endif //LED_BOARD_PROGRAM_BIGANT_HPP
