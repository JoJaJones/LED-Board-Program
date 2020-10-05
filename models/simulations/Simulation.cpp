//
// Created by theom on 9/26/2020.
//

#include "Simulation.hpp"
namespace LEDBoard {
    template<class T>
    Simulation<T>::Simulation(LEDBoard::DataState *state) : Model<LEDBoard::Position<T>>(state) {
        maxStepNum = stepNum = 0;
        runForever = true;
    }

    template<class T>
    Simulation<T>::Simulation(LEDBoard::DataState *state, int maxStep) : Model<Position<T>>(state) {
        stepNum = 0;
        maxStepNum = maxStep;
        runForever = false;
    }

    template<class T>
    void Simulation<T>::initBoard() {
        for (int i = 0; i < NUM_ROWS_OF_PANELS * LED_ROWS_PER_BOARD; ++i) {
            this->board.emplace_back();
            for (int j = 0; j < NUM_COLS_OF_PANELS * LED_COLS_PER_BOARD; ++j) {
                this->board[i].push_back(T());
            }
        }
    }
}