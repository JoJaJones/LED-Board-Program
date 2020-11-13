/****************************************************************************************
 *
 ***************************************************************************************/
#ifndef LED_BOARD_PROGRAM_DATASTATE_HPP
#define LED_BOARD_PROGRAM_DATASTATE_HPP

#include <vector>
#include <board_constants.hpp>
#include <iostream>
#include <set>

namespace LEDBoard {
    using std::vector;
    class DataState {
    private:
        static DataState *state;
        vector<vector<int>> board;
        std::set<std::pair<int, int>> updatedPos;
        vector<Rotations> panelOrientations;
        int numPanels, numPanelRows, numPanelCols;
        int defaultColor;
        static int numReferences;
        explicit DataState(int defaultColor);
        DataState(int defaultColor, int numPanels, int numRows, int numCols, vector <Rotations> &panelConfigs);
        ~DataState();
        void initBoard();
    public:
        static DataState* getInstance();
        static DataState* getInstance(int defaultColor);
        static DataState* getInstance(int defaultColor, int numPanels, int numRows, int numCols, vector<Rotations> panelConfigs);
        void setDefaultColor(int color);
        void setPanelNum(int panelCount);
        void setPanelRows(int numRows);
        void setPanelCols(int numCols);
        void setPanelOrientations(vector <Rotations> &orientations);
        void updateDisplaySettings(int color, int numPanel, int numRow, int numCol, vector <Rotations> &orientations);
        static DataState* releaseReference();
        void setPixel(int *pos, int colorValue, bool isRawPos = true);
        void setPixel(vector<int *> coords, vector<int> colorValues, bool isRawPos = true);
        void setArea(int* pos0, int* pos1, vector<vector<int>> &data);
        void convertPos(int* pos);
        void calcLocalPos(int* pos, int boardNum);
        vector<vector<int>>* getBoard();
        void printBoard();
        std::set<std::pair<int, int>>* getUpdatedPos();
        void clearUpdated();
    };


}



#endif //LED_BOARD_PROGRAM_DATASTATE_HPP
