//
// Created by theom on 9/26/2020.
//

#ifndef LED_BOARD_PROGRAM_ANIMATION_HPP
#define LED_BOARD_PROGRAM_ANIMATION_HPP

#include <Model.hpp>

namespace LEDBoard {
    class Animation : public Model<int> {
    public:
        using Model<int>::Model;

        explicit Animation(DataState *state):Model(state){

        };
    };
}


#endif //LED_BOARD_PROGRAM_ANIMATION_HPP
