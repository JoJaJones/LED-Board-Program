/****************************************************************************************
 *
 ***************************************************************************************/
#include "AntDataService.hpp"

AntDataService* AntDataService::antSettings = nullptr;

AntDataService *AntDataService::getInstance() {
    if (antSettings == nullptr) {
        antSettings = new AntDataService();
    }
    return antSettings;
}

int AntDataService::getNumColors() const {
    return numColors;
}

AntDataService::~AntDataService() {
    antSettings = nullptr;
}

AntDataService::AntDataService() {
    numColors = 2;
    antDefaultColor = LEDBoard::BLUE;
}

LEDBoard::Colors AntDataService::getDefaultColor() {
    return antDefaultColor;
}
