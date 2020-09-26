//
// Created by theom on 9/25/2020.
//

#ifndef LED_BOARD_PROGRAM_DATASTATE_HPP
#define LED_BOARD_PROGRAM_DATASTATE_HPP

#include <vector>
#include <board_constants.hpp>

namespace LEDBoard {
    using std::vector;
    class DataState {
    private:
        vector<vector<int>> board;
        vector<int*> updatedPos;
        vector<LEDBoard::Rotations> panelOrientations;

    public:
        explicit DataState(int defaultColor);
        void setPixel(int *pos, int colorValue);
        void setPixel(vector<int *> coords, vector<int> colorValues);
        void setArea(int* pos0, int* pos1, vector<vector<int>> data);
        void convertPos(int* pos);
        void calcLocalPos(int* pos, int boardNum);
    };
}


#endif //LED_BOARD_PROGRAM_DATASTATE_HPP
