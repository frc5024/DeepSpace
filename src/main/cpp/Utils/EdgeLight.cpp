#include "Utils/EdgeLight.h"
#include <iostream>

LedColour Utils::EdgeLight::ledbuffer = LedColour::kSOLID_WHITE;
frc::Spark* Utils::EdgeLight::pLEDController =  new frc::Spark(LEDCONTROLLER_ID);

void Utils::EdgeLight::Append(LedColour colour){
    Utils::EdgeLight::ledbuffer = colour;
}

void Utils::EdgeLight::Push(){
    if(DODEBUG){
        std::cout << "LED COLOUR: " << Utils::EdgeLight::ledbuffer / (double)100 << std::endl;
    }
    Utils::EdgeLight::pLEDController->Set(Utils::EdgeLight::ledbuffer);
}

