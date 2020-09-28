//
// Created by theom on 9/28/2020.
//

#include "GradualGradient.hpp"

LEDBoard::GradualGradient::GradualGradient(LEDBoard::DataState *state) : Animation(state) {
    curCol = curRow = 0;
    rowColorShift = 24;
    colColorShift = 16;
    resetBoard();
}

void LEDBoard::GradualGradient::processStep() {
    curCol++;
    if(!board.empty() && curCol >= board[0].size()) {
        curCol = 0;
        curRow++;
    }

    int numRows = NUM_ROWS_OF_PANELS * LED_ROWS_PER_BOARD;
    int numCols = NUM_COLS_OF_PANELS * LED_COLS_PER_BOARD;

    if(curRow == 0) {
        board[curRow][curCol] = board[curRow][curCol - 1] - ((0xff / numRows) << rowColorShift);
    } else if(curRow < board.size()) {
        board[curRow][curCol] = board[curRow - 1][curCol] - ((0xff / numCols) << colColorShift);
    } else {
        resetBoard();
    }


}

void LEDBoard::GradualGradient::updateBoard() {
    int pos[2] {curRow, curCol};
    viewBoard->setPixel(pos, board[curRow][curCol]);
}

void LEDBoard::GradualGradient::resetBoard() {
    curRow = curCol = 0;

    Animation::resetBoard(0);
    board[0][0] = 0xffffff;
    Model::updateBoard();
    rowColorShift -= 8;
    if(rowColorShift < 0) {
        rowColorShift = 16;
    }
    colColorShift -= 8;
    if(colColorShift < 0){
        colColorShift = 16;
    }
}


