//
// Created by theom on 9/25/2020.
//

#include <DataState.hpp>
#include <iostream>
#include <board_constants.hpp>
#include <assert.h>

using std::vector;
using std::cout;
using std::endl;

void testBasicInit();

LEDBoard::DataState* testConfigurableInit();
void validateConfig(LEDBoard::DataState *state, int numPanels, int numPanelRows, int numPanelCols,
                    vector<LEDBoard::Rotations> panelConfig);
void testPosConversion(LEDBoard::DataState* state);
void testSetPixel(int *pos, int color, LEDBoard::DataState *state);
void testSetPixels(vector<int *> &pos, vector<int> &color, LEDBoard::DataState *state);
void testSetArea(int *pos0, int *pos1, vector<vector<int>> colors, LEDBoard::DataState *state);
void printData(vector<vector<int>> *board);

int main() {
    testBasicInit();
    LEDBoard::DataState *testState = testConfigurableInit();
    testPosConversion(testState);
    vector<int*> pos {new int[2]{5,5}, new int[2]{5, 40}, new int[2]{40,40}, new int[2]{40, 5}};
    for (int i = 0; i < pos.size(); ++i) {
        int r = pos[i][0], c = pos[i][1];
        testSetPixel(pos[i], 3, testState);
        pos[i][0] = r;
        pos[i][1] = c;
    }

    vector<int> colors {2, 3, 4, 5};
    testSetPixels(pos, colors, testState);
    int pos0[2]{4,4};
    int pos1[2]{6,6};

    vector<vector<int>> colorArr {{1,2,3},{4,5,6},{7,8,9}};
    testSetArea(pos0, pos1, colorArr, testState);

    printData(testState->getBoard());
    delete testState;
    return 0;
}

void testBasicInit(){
    LEDBoard::DataState test(1);
    vector<vector<int>>* testBoard = test.getBoard();
    cout<<"Test Basic Init"<<endl;
    assert(testBoard->size() == LEDBoard::LED_ROWS_PER_BOARD);
    assert(testBoard[0].size() == LEDBoard::LED_COLS_PER_BOARD * LEDBoard::BOARD_CHAIN_LEN);
    cout<<endl;
}


LEDBoard::DataState* testConfigurableInit(){
    int numPanels = 2, numPanelRows = 1, numPanelCols = 2;
    vector<LEDBoard::Rotations> panelConfig {LEDBoard::NONE, LEDBoard::CLOCKWISE};
    auto *test = new LEDBoard::DataState(5, numPanels, numPanelRows, numPanelCols,
                                         panelConfig);
    cout<<"Test first DataState Init"<<endl;
    validateConfig(test, numPanels, numPanelRows, numPanelCols, panelConfig);
    delete test;

    numPanelCols--;
    numPanelRows++;
    test = new LEDBoard::DataState(2, numPanels, numPanelRows, numPanelCols, panelConfig);
    cout<<"Test second DataState Init"<<endl;
    validateConfig(test, numPanels, numPanelRows, numPanelCols, panelConfig);

    numPanels += 2;
    numPanelCols ++;
    panelConfig.push_back(LEDBoard::DOWN);
    panelConfig.push_back(LEDBoard::COUNTERCLOCKWISE);

    test = new LEDBoard::DataState(0, numPanels, numPanelRows, numPanelCols, panelConfig);
    cout<<"Test final DataState Init"<<endl;
    validateConfig(test, numPanels, numPanelRows, numPanelCols, panelConfig);

    cout<<endl;
    return test;
}

void validateConfig(LEDBoard::DataState *state, int numPanels, int numPanelRows, int numPanelCols,
                    vector<LEDBoard::Rotations> panelConfig) {
    vector<vector<int>>* testBoard = state->getBoard();
    assert(testBoard->size() == LEDBoard::LED_ROWS_PER_BOARD);
    assert((*testBoard)[0].size() == numPanels * LEDBoard::LED_COLS_PER_BOARD);

}

void testPosConversion(LEDBoard::DataState *state) {
    int pos[2] = {1, 1};
    cout<<"Test no rotation positions\nBefore: "<<pos[0]<<" "<<pos[1]<<endl;
    state->convertPos(pos);
    cout<<"After: "<<pos[0]<<" "<<pos[1]<<endl<<endl;

    assert(pos[0] == pos[1]);
    assert(pos[0] == 1);

    pos[0] = 0;
    pos[1] = 32;
    cout<<"Test clockwise rotation positions\nBefore: "<<pos[0]<<" "<<pos[1]<<endl;
    state->convertPos(pos);
    cout<<"After first: "<<pos[0]<<" "<<pos[1]<<endl;
    assert(pos[0] == 0);
    assert(pos[1] == 63);

    state->convertPos(pos);
    cout<<"After second: "<<pos[0]<<" "<<pos[1]<<endl;
    assert(pos[0] == 31);
    assert(pos[1] == 63);

    state->convertPos(pos);
    cout<<"After third: "<<pos[0]<<" "<<pos[1]<<endl;
    assert(pos[0] == 31);
    assert(pos[1] == 32);

    state->convertPos(pos);
    cout<<"After fourth: "<<pos[0]<<" "<<pos[1]<<endl;
    assert(pos[0] == 0);
    assert(pos[1] == 32);

    state->convertPos(pos);
    cout<<"After fifth: "<<pos[0]<<" "<<pos[1]<<endl<<endl;
    assert(pos[0] == 0);
    assert(pos[1] == 63);

    pos[0] = 32;
    cout<<"Test 180 rotation positions\nBefore: "<<pos[0]<<" "<<pos[1]<<endl;
    state->convertPos(pos);
    cout<<"After first: "<<pos[0]<<" "<<pos[1]<<endl;

    assert(pos[0] == 31);
    assert(pos[1] == 64);

    pos[0] = 63; pos[1] = 32;

    state->convertPos(pos);
    cout<<"After second: "<<pos[0]<<" "<<pos[1]<<endl;
    assert(pos[0] == 0);
    assert(pos[1] == 64 + 31);
    pos[0] = 32; pos[1] = 63;

    state->convertPos(pos);
    cout<<"After third: "<<pos[0]<<" "<<pos[1]<<endl<<endl;
    assert(pos[0] == 31);
    assert(pos[1] == 64);
    pos[0] = 63; pos[1] = 32;


    pos[1] = 31;
    cout<<"Test counter-clockwise rotation positions\nBefore: "<<pos[0]<<" "<<pos[1]<<endl;
    state->convertPos(pos);
    cout<<"After first: "<<pos[0]<<" "<<pos[1]<<endl;

    assert(pos[0] == 0);
    assert(pos[1] == 96 + 31);

    state->convertPos(pos);
    cout<<"After second: "<<pos[0]<<" "<<pos[1]<<endl;
    assert(pos[0] == 0);
    assert(pos[1] == 96);

    state->convertPos(pos);
    cout<<"After third: "<<pos[0]<<" "<<pos[1]<<endl;
    assert(pos[0] == 31);
    assert(pos[1] == 96);

    state->convertPos(pos);
    cout<<"After fourth: "<<pos[0]<<" "<<pos[1]<<endl;
    assert(pos[0] == 31);
    assert(pos[1] == 31 + 96);

    state->convertPos(pos);
    cout<<"After fifth: "<<pos[0]<<" "<<pos[1]<<endl<<endl;
    assert(pos[0] == 0);
    assert(pos[1] == 96 + 31);
}

void testSetPixel(int *pos, int color, LEDBoard::DataState *state) {
    state->setPixel(pos, color, true);
    vector<vector<int>>* board = state->getBoard();
    assert((*board)[pos[0]][pos[1]] == color);
}

void testSetPixels(vector<int *> &pos, vector<int> &color, LEDBoard::DataState *state) {
    state->setPixel(pos, color);
    vector<vector<int>> *board = state->getBoard();
    for (int i = 0; i < pos.size(); ++i) {
        assert((*board)[pos[i][0]][pos[i][1]] == color[i]);
    }

}

void testSetArea(int *pos0, int *pos1, vector<vector<int>> colors, LEDBoard::DataState *state) {
    state->setArea(pos0, pos1, colors);
    vector<vector<int>> *board = state->getBoard();
    int pos[2] {0,0};
    int r_diff = pos1[0] - pos0[0];
    int c_diff = pos1[1] - pos0[1];
    for (int r = 0; r < r_diff; ++r) {
        for (int c = 0; c < c_diff; ++c) {
            pos[0] = r + pos0[0];
            pos[1] = c + pos0[1];
            state->convertPos(pos);
            assert(colors[r][c] == (*board)[pos[0]][pos[1]]);
        }

    }
}

void printData(vector<vector<int>> *data){
    for(auto row : *data){
        for(auto col : row){
            cout<<col;
        }
        cout<<endl;
    }
}


