//
// Created by theom on 10/6/2020.
//

#include <cmath>
#include "TurnBehavior.hpp"

bool isRelativePrime(int a, int b){
    if(abs(a) == b) {
        return false;
    }

    a = abs(a);

    if(a > b){
        int temp = a;
        a = b;
        b = temp;
    }

    for (int i = 1; i < (b / 2) + 1; ++i) {
        if((i*a) % b == 0){
            return false;
        }
    }

    return true;
}

TurnBehavior::TurnBehavior(int turnType, int numColors) {
    this->turnType = turnType;
    this->numColors = numColors;
    loadDirMods();
}

void TurnBehavior::loadDirMods() {
    while(!isRelativePrime(turnType, numColors)){
        turnType--;
    }

    int multiplier = 1;
    int shift = 0;
    for (int i = 0; i < numColors && i < NUM_DIRECTIONS - 1; ++i) {
        shift += turnType * multiplier;
        while (shift < 0) {
            shift += NUM_DIRECTIONS;
        }
        shift %= NUM_DIRECTIONS;
        if (i & 1) {
            multiplier = -multiplier + 1;
        } else {
            multiplier = -multiplier - 1;
        }
        dirMods.push_back(shift);
    }

    if(numColors == NUM_DIRECTIONS){
        dirMods.push_back(0);
    }
}

Direction TurnBehavior::turn(int colorVal, Direction dir) {
    return LEFT;
}

std::vector<int> *TurnBehavior::getdirMods() {
    return &dirMods;
}

