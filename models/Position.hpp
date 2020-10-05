//
// Created by theom on 9/26/2020.
//

#ifndef LED_BOARD_PROGRAM_POSITION_HPP
#define LED_BOARD_PROGRAM_POSITION_HPP

namespace LEDBoard {
    template <class T>
    class Position {
    protected:
        int color;
        T occupants;
    public:
        virtual void isOccupied() = 0;
        virtual T *getOccupants() = 0;
        virtual int getColor() = 0;
    };
}


#endif //LED_BOARD_PROGRAM_POSITION_HPP
