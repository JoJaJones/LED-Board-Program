//
// Created by theom on 9/26/2020.
//

#include <animations/RandomPixels.hpp>
#include <Model.hpp>


int main(){
    auto *state = new LEDBoard::DataState();
    LEDBoard::Model<int> *testAnim = new LEDBoard::RandomPixels(state);
    state->printBoard(); // 10523
    testAnim->processFrame();
    std::cout<<std::endl<<std::endl;
    state->printBoard(); // 8633

    return 0;
}