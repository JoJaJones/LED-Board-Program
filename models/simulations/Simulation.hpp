/****************************************************************************************
 *
 ***************************************************************************************/
#ifndef LED_BOARD_PROGRAM_SIMULATION_HPP
#define LED_BOARD_PROGRAM_SIMULATION_HPP

#include <DisplayModel.hpp>
#include <Position.hpp>

namespace LEDBoard {
    template <class T>
    class Simulation : public DisplayModel<T>{
    private:
        int stepNum, maxStepNum;
        bool runForever;

    public:
        explicit Simulation(int maxStep);
        Simulation();
        void initBoard();
    };
}


#endif //LED_BOARD_PROGRAM_SIMULATION_HPP
