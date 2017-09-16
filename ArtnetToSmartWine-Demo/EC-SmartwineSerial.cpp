//
//  EC-SmartWine-Serial.cpp
//  EC-SmartWine-Serial
//
//  Created by Sébastien Albert on 02/08/2017.
//
//

#include "EC-SmartwineSerial.h"
#include "NCNS-ArduinoTools.h"

/*
  Vitesse: 19200 bauds
  Nombre de bits: 8
  Parité; sans
  Nombre se stops: 1
  Contrôle de flux: sans
*/

// --------------------------------------------------------------------
// Sending color to all elements (Robinets + Left & Right Bottles)
String SmartwineSerial::getStrGeneral(uint32_t _color) {

  String msg;
  msg += "@LED_ALL";
  msg += getColorString(_color);
  msg += getColorString(_color);
  msg += getColorString(_color);
  msg += getTermination();
  //msg += (char)Ox0A;

  return msg;

}
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// Sending color to particular elements
String SmartwineSerial::getStrRobinets(uint32_t _color) {
  //""
  String msg;
  msg += "@LED_R";
  msg += getColorString(_color);
  msg += getTermination();
  //msg += (char)Ox0A;

  return msg;
}

// --------------------------------------------------------------------
String SmartwineSerial::getStrLeftBottles(uint32_t _color) {
  //"@LED_B_G_"
  String msg;
  msg += "@LED_B_G";
  msg += getColorString(_color);
  msg += getTermination();

  return msg;
}

// --------------------------------------------------------------------
String SmartwineSerial::getStrRightBottles(uint32_t _color) {
  //"@LED_B_D_"
  String msg;
  msg += "@LED_B_D";
  msg += getColorString(_color);
  msg += getTermination();

  return msg;
}

// --------------------------------------------------------------------
String SmartwineSerial::getColorString(uint32_t _color) {

  int redMapped = map((int)Red(_color), 0, 255, 0, 31);
  int greenMapped = map((int)Green(_color), 0, 255, 0, 31);
  int blueMapped = map((int)Blue(_color), 0, 255, 0, 31);

  String redChar = String(redMapped, DEC);
  if (redChar.length() < 2) {
    redChar = '0' + redChar;
  }

  String greenChar = String(greenMapped, DEC);
  if (greenChar.length() < 2) {
    greenChar = '0' + greenChar;
  }

  String blueChar = String(blueMapped, DEC);
  if (blueChar.length() < 2) {
    blueChar = '0' + blueChar;
  }

  String colorString;

  colorString += "_";
  colorString += redChar;
  colorString += "_";
  colorString += greenChar;
  colorString += "_";
  colorString += blueChar;

  return colorString;

}
// --------------------------------------------------------------------

// --------------------------------------------------------------------
String SmartwineSerial::getTermination() {
  return "\r\n";
}
// --------------------------------------------------------------------

/*************************************************
  Returns the Red component of a 32-bit color
**************************************************/
uint8_t SmartwineSerial::Red(uint32_t color)
{
  return (color >> 16) & 0xFF;
}

/*************************************************
  Returns the Green component of a 32-bit color
**************************************************/
uint8_t SmartwineSerial::Green(uint32_t color)
{
  return (color >> 8) & 0xFF;
}

/*************************************************
  Returns the Blue component of a 32-bit color
**************************************************/
uint8_t SmartwineSerial::Blue(uint32_t color)
{
  return color & 0xFF;
}

