/****************************************************************************************
 *
 ***************************************************************************************/
#ifndef LED_BOARD_PROGRAM_RANDOMPIXELS_HPP
#define LED_BOARD_PROGRAM_RANDOMPIXELS_HPP

#include "Animation.hpp"

namespace LEDBoard {
    class RandomPixels : public Animation {
    private:
        void generateColor(int &curColor);
    public:
        RandomPixels();
        void processStep() override;

    };
}


#endif //LED_BOARD_PROGRAM_RANDOMPIXELS_HPP
