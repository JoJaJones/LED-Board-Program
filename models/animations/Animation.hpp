/****************************************************************************************
 *
 ***************************************************************************************/
#ifndef LED_BOARD_PROGRAM_ANIMATION_HPP
#define LED_BOARD_PROGRAM_ANIMATION_HPP

#include <Model.hpp>

namespace LEDBoard {
    class Animation : public Model<int> {
    public:

        Animation();
        explicit Animation(int startVal);
        void initBoard(int val);
        void resetBoard(int val);
    };
}


#endif //LED_BOARD_PROGRAM_ANIMATION_HPP
