//
// Created by theom on 9/25/2020.
//

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
