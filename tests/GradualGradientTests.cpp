/****************************************************************************************
 *
 ***************************************************************************************/
#include <animations/GradualGradient.hpp>


int main() {
    auto *state = LEDBoard::DataState::getInstance();
    LEDBoard::DisplayModel<int> *testAnim = new LEDBoard::GradualGradient();

    int count = 1;
    while(count <= 1024 * 3){
        testAnim->processFrame();
        if(++count % 1024 == 0){
            state->printBoard();
        }
    }
    return 0;
}