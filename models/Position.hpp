//
// Created by theom on 9/26/2020.
//

#ifndef LED_BOARD_PROGRAM_POSITION_HPP
#define LED_BOARD_PROGRAM_POSITION_HPP

#include <constants.hpp>

namespace LEDBoard {
    template <class T>
    class Position {
    protected:
        Colors color;
        T occupants;
    public:
        explicit Position(Colors color);
        virtual void isOccupied() = 0;
        virtual T *getOccupants() = 0;
        virtual int getColor() = 0;
    };

    template<class T>
    Position<T>::Position(Colors color) : color(color) {}
}


#endif //LED_BOARD_PROGRAM_POSITION_HPP
