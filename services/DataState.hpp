//
// Created by theom on 9/25/2020.
//

#ifndef LED_BOARD_PROGRAM_DATASTATE_HPP
#define LED_BOARD_PROGRAM_DATASTATE_HPP

#include <vector>
#include <board_constants.hpp>
#include <iostream>

namespace LEDBoard {
    using std::vector;
    class DataState {
    private:
        vector<vector<int>> board;
        vector<int*> updatedPos;
        vector<LEDBoard::Rotations> panelOrientations;
        int numPanels, numPanelRows, numPanelCols;
        int midRow, midCol;
        void initBoard(int defaultColor);


    public:
        DataState();
        explicit DataState(int defaultColor);
        DataState(int defaultColor, int numPanels, int numPanelRows, int numPanelCols,
                  vector <Rotations> panelConfigs);
        void setPixel(int *pos, int colorValue, bool isRawPos = true);
        void setPixel(vector<int *> coords, vector<int> colorValues, bool isRawPos = true);
        void setArea(int* pos0, int* pos1, vector<vector<int>> &data);
        void convertPos(int* pos);
        void calcLocalPos(int* pos, int boardNum);
        vector<vector<int>>* getBoard();
        void printBoard();
    };
}


#endif //LED_BOARD_PROGRAM_DATASTATE_HPP
