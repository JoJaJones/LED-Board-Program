//
// Created by theom on 9/28/2020.
//

#include <animations/GradualGradient.hpp>


int main() {
    auto *state = new LEDBoard::DataState();
    LEDBoard::Model<int> *testAnim = new LEDBoard::GradualGradient(state);

    int count = 1;
    while(count <= 1024 * 3){
        testAnim->processFrame();
        if(count++ % 1024 == 0){
            state->printBoard();
        }
    }
    return 0;
}