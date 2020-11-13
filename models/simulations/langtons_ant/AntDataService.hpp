/****************************************************************************************
 *
 ***************************************************************************************/
#ifndef LED_BOARD_PROGRAM_ANTDATASERVICE_HPP
#define LED_BOARD_PROGRAM_ANTDATASERVICE_HPP


#include <constants.hpp>

class AntDataService {
private:
    int numColors;
    LEDBoard::Colors antDefaultColor;
    static AntDataService *antSettings;
    AntDataService();
public:
    static AntDataService* getInstance();
    ~AntDataService();
    int getNumColors() const;
    LEDBoard::Colors getDefaultColor();
};


#endif //LED_BOARD_PROGRAM_ANTDATASERVICE_HPP
