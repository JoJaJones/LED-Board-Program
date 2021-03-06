//
// Created by theom on 9/26/2020.
//

#ifndef LED_BOARD_PROGRAM_GAME_HPP
#define LED_BOARD_PROGRAM_GAME_HPP

#include <Position.hpp>
#include <Model.hpp>

namespace LEDBoard {
    template <class T>
    class Game : public Model<Position<T>> {
    public:
        virtual bool makeMove(int* start, int* end) = 0;
    };
}


#endif //LED_BOARD_PROGRAM_GAME_HPP
