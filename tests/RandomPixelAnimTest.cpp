/****************************************************************************************
 *
 ***************************************************************************************/
#include <animations/RandomPixels.hpp>

int main(){
    auto *state = LEDBoard::DataState::getInstance();
    LEDBoard::Model<int> *testAnim = new LEDBoard::RandomPixels();
    state->printBoard(); // 10523
    testAnim->processFrame();
    std::cout<<std::endl<<std::endl;
    state->printBoard(); // 8633

    return 0;
}