/****************************************************************************************
 *
 ***************************************************************************************/
#include "DisplayModel.hpp"

// prevents linker issue when inheriting from the specialized class Animation
template class LEDBoard::DisplayModel<int>;

template <>
void LEDBoard::DisplayModel<int>::updateBoard() {
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
void LEDBoard::DisplayModel<T>::updateBoard() {
    int pos[2];
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].size(); ++j) {
            pos[0] = i;
            pos[1] = j;
            viewBoard->setPixel(pos, board[i][j].getColor());
        }
    }
}

template <class T>
void LEDBoard::DisplayModel<T>::processFrame() {
    processStep();
    updateBoard();
}

template<class T>
LEDBoard::DisplayModel<T>::~DisplayModel() {
    viewBoard->releaseReference();
}

template<class T>
LEDBoard::DisplayModel<T>::DisplayModel() {
    viewBoard = DataState::getInstance();
}

