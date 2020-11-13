/****************************************************************************************
 *
 ***************************************************************************************/
#include <cstdlib>
#include <ctime>
#include "RandomPixels.hpp"

LEDBoard::RandomPixels::RandomPixels() : Animation() {
    srand(time(nullptr));
    processFrame();
}

void LEDBoard::RandomPixels::processStep() {
    for (auto &i : board) {
        for (int &j : i) {
            generateColor(j);
        }

    }
}

void LEDBoard::RandomPixels::generateColor(int &curColor) {
    int r = (curColor&0xff0000)>>16, g = (curColor&0xff00)>>8, b = curColor&0xff;
    if(r <= 1) {
        r = rand() % 0x100;
        r <<= 16;
    } else {
        r -= rand() % (r / 2);
    }

    if(g <= 1) {
        g = rand() % 0x100;
        g<<= 8;
    } else {
        g -= rand() % (g / 2);
        g<<=8;
    }

    if(b <= 1) {
        b = rand() % 0x100;
        b <<= 8;
    } else {
        b -= rand() % (b / 2);
    }

    curColor = r + g + b;
}


