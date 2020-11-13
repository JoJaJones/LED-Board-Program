/***********************************************************************************************************************
 * This cpp provides the implementation for the TurnBehavior class methods and a relevant utility function
 **********************************************************************************************************************/

#include <cmath>
#include "TurnBehavior.hpp"

/***********************************************************************************************************************
 * Function to determine if two integers are prime in relation to each other to prevent turnType integers that are
 * incompatible with the number of colors
 **********************************************************************************************************************/
bool isRelativePrime(int a, int b){
    if(abs(a) == b) {
        return false;
    }

    a = abs(a);

    // if a is bigger than b then we need to swap them for the algorithm to work
    if(a > b){
        int temp = a;
        a = b;
        b = temp;
    }

    // check is multiples of a up to half of b are divisible by b, if so they are not relatively prime
    for (int i = 1; i < (b / 2) + 1; ++i) {
        if((i*a) % b == 0){
            return false;
        }
    }

    return true;
}

/***********************************************************************************************************************
 * Constructor for the TurnBehavior class
 **********************************************************************************************************************/
TurnBehavior::TurnBehavior(int turnType, int numColors) : turnType(turnType), numColors(numColors) {
    loadDirMods();
}

/***********************************************************************************************************************
 * Function to initialize the dirMods vector so that it knows how much to shift the language based on the index the
 * color belongs to in the position's color list (this allows each position to be given a different set of colors as
 * long as the number of colors is uniform across all positions)
 **********************************************************************************************************************/
void TurnBehavior::loadDirMods() {
    // if the values are not relatively prime reduce turn type until they are (sanitize the value)
    while(!isRelativePrime(turnType, numColors)){
        turnType--;
    }

    int multiplier = 1;
    int shift = 0;

    // This creates multipliers of the turnType in the pattern 1, -2, 3, -4, etc until the number of colors or
    // number of directions is reached and stores the results in the last index of dirMods to create
    // list of modifiers that are alternating directions every iteration and in increasing magnitudes every other
    // iteration
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

    // handle situation where there is a color for every direction by setting the behavior to continue current heading
    if(numColors == NUM_DIRECTIONS){
        dirMods.push_back(0);
    }
}

/***********************************************************************************************************************
 * Function to handle changes in direction for the Ant.
 *
 * @param colorVal: index of the color of the position the Ant is turning on
 * @param dir: Ant's current heading
 * @return: Direction that is the result of applying the appropriate modification based on color index
 **********************************************************************************************************************/
Direction TurnBehavior::turn(int colorVal, Direction dir) {
    int tempDir = dir + dirMods[colorVal];
    tempDir %= NUM_DIRECTIONS;
    return static_cast<Direction>(tempDir);
}

/***********************************************************************************************************************
 * Get function used in unit tests to verify integrity of algorithm to load the direction mods vector
 **********************************************************************************************************************/
std::vector<int> *TurnBehavior::getdirMods() {
    return &dirMods;
}

