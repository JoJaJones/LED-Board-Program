//
// Created by theom on 9/25/2020.
//

#include "DataState.hpp"
#include "constants.hpp"

#include <iostream>

int LEDBoard::DataState::numReferences = 0;
LEDBoard::DataState* LEDBoard::DataState::state = nullptr;

LEDBoard::DataState::DataState(int defaultColor) {
    numPanels = BOARD_CHAIN_LEN;
    numPanelCols = NUM_COLS_OF_PANELS;
    numPanelRows = NUM_ROWS_OF_PANELS;
    this->defaultColor = defaultColor;

    initBoard();

    for (auto i : PANEL_CONFIGURATION) {
        panelOrientations.push_back(i);
    }
}

LEDBoard::DataState::DataState(int defaultColor, int numPanels, int numRows, int numCols,
                               vector <Rotations> &panelConfigs) {
    this->numPanels = numPanels;
    this->numPanelRows = numRows;
    this->numPanelCols = numCols;
    this->defaultColor = defaultColor;

    initBoard();

    for (auto i : panelConfigs){
        panelOrientations.push_back(i);
    }
}

void LEDBoard::DataState::initBoard() {
    while(board.size() > LED_ROWS_PER_BOARD){
        board.pop_back();
    }

    while(board.size() < LED_ROWS_PER_BOARD){
        board.emplace_back();
    }
    for(int i = 0; i < LED_ROWS_PER_BOARD; ++i){
        for (int j = 0; j < board[i].size() && j < LED_COLS_PER_BOARD * numPanels; ++j) {
            board[i][j] = defaultColor;
        }
        while(board[i].size() < LED_COLS_PER_BOARD * numPanels) {
            board[i].push_back(defaultColor);
        }
        while(board[i].size() > LED_COLS_PER_BOARD * numPanels) {
            board[i].pop_back();
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
    updatedPos.emplace(r, c);
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
        updatedPos.emplace(r, c);
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
            updatedPos.emplace(tempPos[R_IDX], tempPos[C_IDX]);
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

LEDBoard::DataState::~DataState() {
    state = nullptr;
    numReferences = 0;
};

LEDBoard::DataState *LEDBoard::DataState::getInstance() {
    if(state == nullptr) {
        getInstance(0);
    }else {
        numReferences++;
    }
    return state;
}

LEDBoard::DataState *LEDBoard::DataState::getInstance(int defaultColor) {
    if(state == nullptr) {
        state = new DataState(defaultColor);
    }
    numReferences++;
    return state;
}

LEDBoard::DataState *LEDBoard::DataState::getInstance(int defaultColor, int numPanels, int numRows, int numCols,
                                                      std::vector<LEDBoard::Rotations> panelConfigs) {
    if(state == nullptr){
        state = new DataState(defaultColor, numPanels, numRows, numCols, panelConfigs);
    }
    numReferences++;
    return state;
}

LEDBoard::DataState* LEDBoard::DataState::releaseReference() {
    if (numReferences > 0) {
        numReferences--;
    } else if (numReferences == 0) {
        delete state;
    }

    return nullptr;
}

void LEDBoard::DataState::setDefaultColor(int color) {
    updateDisplaySettings(color, numPanels, numPanelRows, numPanelCols, panelOrientations);
}

void LEDBoard::DataState::setPanelNum(int panelCount) {
    updateDisplaySettings(defaultColor, panelCount, numPanelRows, numPanelCols, panelOrientations);
}

void LEDBoard::DataState::setPanelRows(int numRows) {
    updateDisplaySettings(defaultColor, numPanels, numRows, numPanelCols, panelOrientations);
}

void LEDBoard::DataState::setPanelCols(int numCols) {
    updateDisplaySettings(defaultColor, numPanels, numPanelRows, numCols, panelOrientations);
}

void LEDBoard::DataState::setPanelOrientations(vector <Rotations> &orientations) {
    updateDisplaySettings(defaultColor, numPanels, numPanelRows, numPanelCols, orientations);
}

void LEDBoard::DataState::updateDisplaySettings(int color, int numPanel, int numRow, int numCol,
                                                vector <Rotations> &orientations) {
    this->defaultColor = color;
    this->numPanels = numPanel;
    this->numPanelRows = numRow;
    this->numPanelCols = numCol;

    for (int i = 0; i < orientations.size(); ++i) {
        if(i < this->panelOrientations.size()) {
            this->panelOrientations[i] = orientations[i];
        } else {
            this->panelOrientations.push_back(orientations[i]);
        }
    }

    initBoard();
}

std::set<std::pair<int, int>> *LEDBoard::DataState::getUpdatedPos() {
    return &updatedPos;
}

void LEDBoard::DataState::clearUpdated() {
    updatedPos.clear();
}


