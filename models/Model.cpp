/****************************************************************************************
 *
 ***************************************************************************************/
#include "Model.hpp"

// prevents linker issue when inheriting from the specialized class Animation
template class LEDBoard::Model<int>;

template <>
void LEDBoard::Model<int>::updateBoard() {
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
void LEDBoard::Model<T>::updateBoard() {
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
void LEDBoard::Model<T>::processFrame() {
    processStep();
    updateBoard();
}

template<class T>
LEDBoard::Model<T>::~Model() {
    viewBoard->releaseReference();
}

template<class T>
LEDBoard::Model<T>::Model() {
    viewBoard = DataState::getInstance();
}

