/****************************************************************************************
 *
 ***************************************************************************************/
#include "Position.hpp"
template<class T>
void LEDBoard::Position<T>::addToPosition(T *element) {
    occupants.push_back(element);
}

template<class T>
T *LEDBoard::Position<T>::removeFromPosition(int index) {
    T* element = occupants[index];
    occupants.erase(occupants.begin() + index);
    return element;
}