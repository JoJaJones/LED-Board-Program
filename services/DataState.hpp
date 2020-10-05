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
        static DataState *state;
        vector<vector<int>> board;
        vector<int*> updatedPos;
        vector<Rotations> panelOrientations;
        int numPanels, numPanelRows, numPanelCols;
        int midRow, midCol;
        static int numReferences;
        explicit DataState(int defaultColor);
        DataState(int defaultColor, int numPanels, int numRows, int numCols, vector<Rotations> panelConfigs);
        ~DataState();
        void initBoard(int defaultColor);
    public:
        static DataState* getInstance();
        static DataState* getInstance(int defaultColor);
        static DataState* getInstance(int defaultColor, int numPanels, int numRows, int numCols, vector<Rotations> panelConfigs);
        void releaseReference();
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
