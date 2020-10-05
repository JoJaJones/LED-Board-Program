//
// Created by theom on 9/26/2020.
//

#include "Animation.hpp"


LEDBoard::Animation::Animation() : Model<int>() {
    initBoard(0);
}

LEDBoard::Animation::Animation(int startVal): Model<int>() {
    initBoard(startVal);
}

void LEDBoard::Animation::initBoard(int val) {
    for (int i = 0; i < LEDBoard::LED_ROWS_PER_BOARD * LEDBoard::NUM_ROWS_OF_PANELS; ++i) {
        board.emplace_back();
        for (int j = 0; j < LEDBoard::LED_COLS_PER_BOARD * LEDBoard::NUM_COLS_OF_PANELS; ++j) {
            board[i].push_back(val);
        }
    }
}

void LEDBoard::Animation::resetBoard(int val) {
    for (auto & i : board) {
        for (int & j : i) {
            j = val;
        }
    }

}
