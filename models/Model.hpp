/****************************************************************************************
 * File containing the declaration for an abstract Model class to be used by the various
 * simulations, animations, and games. It contains a 2 dimensional vector of a template
 * type to simulate the contents and has functions to process each frame of the animation,
 * simulation, or game. processStep will need to be implemented by each child and
 * updateBoard will need to be overridden in children whose board size does not match the
 * size of the LED board.
 ***************************************************************************************/
#ifndef LED_BOARD_PROGRAM_MODEL_HPP
#define LED_BOARD_PROGRAM_MODEL_HPP

#include <DataState.hpp>

namespace LEDBoard {
    template <class T>
    class Model {
    protected:
        DataState *viewBoard;
        vector<vector<T>> board;

        virtual void processStep() = 0;
        virtual void updateBoard();
    public:
        Model();
        virtual ~Model();
        void processFrame();
    };
}

#endif //LED_BOARD_PROGRAM_MODEL_HPP
