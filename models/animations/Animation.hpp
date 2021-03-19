/****************************************************************************************
 *
 ***************************************************************************************/
#ifndef LED_BOARD_PROGRAM_ANIMATION_HPP
#define LED_BOARD_PROGRAM_ANIMATION_HPP

#include <DisplayModel.hpp>

namespace LEDBoard {
    class Animation : public DisplayModel<int> {
    public:

        Animation();
        explicit Animation(int startVal);
        void initBoard(int val);
        void resetBoard(int val);
    };
}


#endif //LED_BOARD_PROGRAM_ANIMATION_HPP
