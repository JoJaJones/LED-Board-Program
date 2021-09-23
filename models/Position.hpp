/****************************************************************************************
 *
 ***************************************************************************************/
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
        virtual bool isOccupied() = 0;
        virtual T *getOccupants() = 0;
        virtual int getColor() = 0;
        virtual void addToPosition(T* element);
        virtual T *removeFromPosition(int index = 0);
    };

    template<class T>
    Position<T>::Position(Colors color) : color(color) {}
}


#endif //LED_BOARD_PROGRAM_POSITION_HPP
