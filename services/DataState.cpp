//
// Created by theom on 9/25/2020.
//

#include "DataState.hpp"
#include "constants.hpp"

#include <iostream>

LEDBoard::DataState::DataState() : DataState(0) {}

LEDBoard::DataState::DataState(int defaultColor) {
    numPanels = BOARD_CHAIN_LEN;
    numPanelCols = NUM_COLS_OF_PANELS;
    numPanelRows = NUM_ROWS_OF_PANELS;
    midCol = LED_COLS_PER_BOARD/2;
    midRow = LED_ROWS_PER_BOARD/2;

    initBoard(defaultColor);

    for (auto i : PANEL_CONFIGURATION) {
        panelOrientations.push_back(i);
    }
}

LEDBoard::DataState::DataState(int defaultColor, int numPanels, int numPanelRows, int numPanelCols,
                               vector <Rotations> panelConfigs) {
    this->numPanels = numPanels;
    this->numPanelRows = numPanelRows;
    this->numPanelCols = numPanelCols;
    midCol = LED_COLS_PER_BOARD/2;
    midRow = LED_ROWS_PER_BOARD/2;

    initBoard(defaultColor);

    for (auto i : panelConfigs){
        panelOrientations.push_back(i);
    }
}

void LEDBoard::DataState::initBoard(int defaultColor) {
    for(int i = 0; i < LED_ROWS_PER_BOARD; ++i){
        board.emplace_back();
        for (int j = 0; j < LED_COLS_PER_BOARD * numPanels; ++j) {
            board[i].push_back(defaultColor);
        }
    }
}

void LEDBoard::DataState::convertPos(int *pos) {
    int row, col, boardNum = -1;
    if(pos != nullptr){
        row = pos[R_IDX];
        col = pos[C_IDX];
    } else {
        row = col = -1;
    }

    int boardRow;
    if(row < LED_ROWS_PER_BOARD){
        boardRow = 0;
        boardNum = col / LED_COLS_PER_BOARD;
    } else {
        boardRow = row / LED_ROWS_PER_BOARD;
        boardNum = boardRow * numPanelCols;
        if(boardRow % 2 != 0) {
            int totalColsPerRow = numPanelCols * LED_COLS_PER_BOARD;
            boardNum += (totalColsPerRow - (col + 1)) / LED_COLS_PER_BOARD;
        } else {
            boardNum += col/LED_COLS_PER_BOARD;
        }
    }

    pos[R_IDX] = pos[R_IDX]%LED_ROWS_PER_BOARD;
    pos[C_IDX] = pos[C_IDX]%LED_COLS_PER_BOARD;

    if(boardNum >= 0) {
        calcLocalPos(pos, boardNum);
        pos[C_IDX] = pos[C_IDX] + LED_COLS_PER_BOARD * boardNum;
    }
}

// pos in r, c
void LEDBoard::DataState::setPixel(int *pos, int colorValue, bool isRawPos) {
    if(isRawPos) {
        convertPos(pos);
    }
    int r = pos[R_IDX], c = pos[C_IDX];
    board[r][c] = colorValue;
}

void LEDBoard::DataState::setPixel(vector<int *> coords, vector<int> colorValues, bool isRawPos) {
    int r, c;
    for (int i = 0; i < coords.size(); ++i) {
        if(isRawPos) {
            convertPos(coords[i]);
        }
        r = coords[i][R_IDX];
        c = coords[i][C_IDX];
        board[r][c] = colorValues[i];
    }
}

/********************************************************************************************
 * Function that takes 2 of the corners of a rectangle of pixels to be updated and the new
 * colors with which to update them.
 *
 * @param pos0 : coordinate of the top left LED within the rectangle to be updated
 * @param pos1 : coordinate of the bottom right LED within the rectangle to be updates
 * @param data : 2 dimensional array of new color values starting from top left to bottom right
 *******************************************************************************************/
void LEDBoard::DataState::setArea(int *pos0, int *pos1, vector<vector<int>> &data) {
    int tempPos[2] {0};
    int r_diff = pos1[R_IDX] - pos0[R_IDX];
    int c_diff = pos1[C_IDX] - pos0[C_IDX];

    for (int i = 0; i <= r_diff; ++i) {
        for (int j = 0; j <= c_diff; ++j) {
            tempPos[R_IDX] = i + pos0[R_IDX];
            tempPos[C_IDX] = j + pos0[C_IDX];
            convertPos(tempPos);
            board[tempPos[R_IDX]][tempPos[C_IDX]] = data[i][j];
        }
    }
}

void LEDBoard::DataState::calcLocalPos(int *pos, int boardNum) {
    int row, col;
    switch(panelOrientations[boardNum]){
        case CLOCKWISE:
            row = pos[C_IDX];
            col = LED_COLS_PER_BOARD - pos[R_IDX] - 1;
            break;
        case DOWN:
            row = LED_ROWS_PER_BOARD - pos[R_IDX] - 1;
            col = LED_COLS_PER_BOARD - pos[C_IDX] - 1;
            break;
        case COUNTERCLOCKWISE:
            col = pos[R_IDX];
            row = LED_ROWS_PER_BOARD - pos[C_IDX] - 1;
            break;
        default:
            row = pos[R_IDX];
            col = pos[C_IDX];
    }
    pos[R_IDX] = row;
    pos[C_IDX] = col;
}

std::vector<std::vector<int>> *LEDBoard::DataState::getBoard() {
    return &board;
}

void LEDBoard::DataState::printBoard() {
    for (auto & i : board) {
        for (int j : i) {
            std::cout<<j<<" ";
        }
        std::cout<<std::endl;
    }

    std::cout<<std::endl;
}