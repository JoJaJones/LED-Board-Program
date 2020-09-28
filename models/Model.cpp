//
// Created by theom on 9/25/2020.
//

#include "Model.hpp"
template class LEDBoard::Model<int>;

template <class T>
void LEDBoard::Model<T>::updateBoard() {
    int pos[2];
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].size(); ++j) {
            pos[0] = i;
            pos[1] = j;
            viewBoard->setPixel(pos, board[i][j]);
        }
    }
}

template <class T>
void LEDBoard::Model<T>::processFrame() {
    processStep();
    updateBoard();
}

template<class T>
LEDBoard::Model<T>::~Model() {
    delete viewBoard;
}

template<class T>
LEDBoard::Model<T>::Model(LEDBoard::DataState *state) {
    viewBoard = state;
    for (int i = 0; i < LEDBoard::LED_ROWS_PER_BOARD * LEDBoard::NUM_ROWS_OF_PANELS; ++i) {
        board.emplace_back();
        for (int j = 0; j < LEDBoard::LED_COLS_PER_BOARD * LEDBoard::NUM_COLS_OF_PANELS; ++j) {
            board[i].push_back(5);
        }
    }
}

