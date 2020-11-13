/****************************************************************************************
 *
 ***************************************************************************************/
#ifndef LED_BOARD_PROGRAM_GRADUALGRADIENT_HPP
#define LED_BOARD_PROGRAM_GRADUALGRADIENT_HPP

#include <DataState.hpp>
#include "Animation.hpp"

namespace LEDBoard {
    class GradualGradient : public Animation {
    private:
        int curCol, curRow;
        int rowColorShift, colColorShift;

    public:
        GradualGradient();
        void updateBoard() override;
        void processStep() override;
        void resetBoard();
    };
}


#endif //LED_BOARD_PROGRAM_GRADUALGRADIENT_HPP
