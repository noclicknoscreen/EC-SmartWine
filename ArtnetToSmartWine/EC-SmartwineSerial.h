//
//  EC-SmartWine-Serial.hpp
//  EC-SmartWine-Serial
//
//  Created by Sébastien Albert on 02/08/2017.
//
//

#pragma once
#include <Arduino.h>
#include "NCNS-ArduinoTools.h"

#define EC_MSG_ALL     "@LED_ALL"
#define EC_MSG_R       "@LED_R_"
#define EC_MSG_B_G     "@LED_B_G_"
#define EC_MSG_B_D     "@LED_B_D_"

class SmartwineSerial {

  public:
    SmartwineSerial();

  private:
    uint32_t     m_colorRobi;
    uint32_t     m_colorL_Bottles;
    uint32_t     m_colorR_Bottles;

  private:
    String      getColorString(uint32_t _color);
    String      getTermination();

  public:
    String getStrLeftBottles(uint32_t _color);
    String getStrRightBottles(uint32_t _color);
    String getStrRobinets(uint32_t _color);
    String getStrGeneral(uint32_t _color);

    uint8_t Red(uint32_t color);
    uint8_t Green(uint32_t color);
    uint8_t Blue(uint32_t color);

};
