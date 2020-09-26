//
// Created by theom on 9/25/2020.
//

#include "DataState.hpp"
#include "constants.hpp"

LEDBoard::DataState::DataState(int defaultColor) {
    for(int i = 0; i < LED_ROWS_PER_BOARD; ++i){
        board.emplace_back();
        for (int j = 0; j < LED_COLS_PER_BOARD * BOARD_CHAIN_LEN; ++j) {
            board[i].push_back(defaultColor);
        }
    }

    for (auto i : PANEL_CONFIGURATION) {
        panelOrientations.push_back(i);
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

    if(row < NUM_ROWS_OF_PANELS){
        boardNum = col / LED_COLS_PER_BOARD;
    } else {
        int boardRow = row/ LED_ROWS_PER_BOARD;
        boardNum = boardRow * NUM_COLS_OF_PANELS;
        if(boardRow & 1) {
            int totalColsPerRow = NUM_COLS_OF_PANELS * LED_COLS_PER_BOARD;
            boardNum += (totalColsPerRow - col) / LED_COLS_PER_BOARD;
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

void LEDBoard::DataState::setPixel(int *pos, int colorValue) {
    convertPos(pos);
    int r = pos[R_IDX], c = pos[C_IDX];
    board[r][c] = colorValue;
}

void LEDBoard::DataState::setPixel(vector<int *> coords, vector<int> colorValues) {
    int r, c;
    for (int i = 0; i < coords.size(); ++i) {
        convertPos(coords[i]);
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
void LEDBoard::DataState::setArea(int *pos0, int *pos1, std::vector<std::vector<int>> data) {
    int tempPos[2] {0};
    int r_diff = pos1[R_IDX] - pos0[R_IDX];
    int c_diff = pos1[C_IDX] - pos0[C_IDX];

    for (int i = 0; i <= r_diff; ++i) {
        for (int j = 0; j <= c_diff; ++j) {
            tempPos[0] = i + pos0[R_IDX];
            tempPos[1] = j + pos0[C_IDX];
            convertPos(tempPos);
            board[tempPos[0]][tempPos[1]] = data[i][j];
        }
    }
}

void LEDBoard::DataState::calcLocalPos(int *pos, int boardNum) {
    switch(panelOrientations[boardNum]){
        case CLOCKWISE:
            pos[C_IDX] = LED_COLS_PER_BOARD - pos[C_IDX] - 1;
            break;
        case DOWN:
            pos[R_IDX] = LED_ROWS_PER_BOARD - pos[R_IDX] - 1;
            pos[C_IDX] = LED_COLS_PER_BOARD - pos[C_IDX] - 1;
            break;
        case COUNTERCLOCKWISE:
            pos[R_IDX] = LED_ROWS_PER_BOARD - pos[R_IDX] - 1;
            break;
        default: ;
    }
}
