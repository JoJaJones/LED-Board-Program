/****************************************************************************************
 *
 ***************************************************************************************/
#ifndef LED_BOARD_PROGRAM_LEDBOARDENGINE_HPP
#define LED_BOARD_PROGRAM_LEDBOARDENGINE_HPP


#include <DisplayModel.hpp>
#include <View.hpp>
#include <DataState.hpp>

namespace LEDBoard {
    class LEDBoardEngine {
    private:
        LEDBoard::Model *model;
        LEDBoard::View *view;
        LEDBoard::DataState *board;

    public:
        LEDBoardEngine();
        void run();
        void simMenu();
    };
}


#endif //LED_BOARD_PROGRAM_LEDBOARDENGINE_HPP
