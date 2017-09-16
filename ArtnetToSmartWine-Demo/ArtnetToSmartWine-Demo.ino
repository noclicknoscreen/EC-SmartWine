/*
  This is similar to ArtnetReceive but uses a callback to read the data.
  This example may be copied under the terms of the MIT license, see the LICENSE file for details
*/

//#include <SPI.h>

#include "NCNS-ArduinoTools.h"

// ARTNET SECTION ---------------------------------------------------------
#include <Artnet.h>
#include <Ethernet2.h>
#include <EthernetUdp2.h>

Artnet artnet;

// Change ip and mac address for your setup
byte ip[] = {192, 168, 2, 16};
byte mac[] = {0x90, 0xA2, 0xDA, 0x11, 0x2F, 0x18};
// ------------------------------------------------------------------------

// NEOPIXEL SECTION -------------------------------------------------------
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

Adafruit_NeoPixel stripTableA = Adafruit_NeoPixel(7, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripTableB = Adafruit_NeoPixel(7, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripTableC = Adafruit_NeoPixel(7, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripTableD = Adafruit_NeoPixel(7, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripBackLight = Adafruit_NeoPixel(120, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripSmartWine = Adafruit_NeoPixel(30, 7, NEO_GRB + NEO_KHZ800);
// ------------------------------------------------------------------------

// SERIAL SECTION ----------------------------------------------------------
#include "EC-SmartwineSerial.h"
#include "SoftwareSerial.h"

//SmartwineSerial smwSerial;
//SoftwareSerial mySerial(10, 11, true);
// ------------------------------------------------------------------------

void setup()
{
  
  Serial.begin(19200);
  Serial.println();
  Serial.println("Hello World !");
  
  artnet.begin(mac, ip);

  // this will be called for each packet received
  artnet.setArtDmxCallback(onDmxFrame);

  Serial.println("Init Table A");
  InitOneSTrip(&stripTableA);
  Serial.println("Init Table A");
  InitOneSTrip(&stripTableB);
  Serial.println("Init Table A");
  InitOneSTrip(&stripTableC);
  Serial.println("Init Table A");
  InitOneSTrip(&stripTableD);
  Serial.println("Init Table A");
  InitOneSTrip(&stripBackLight);
  Serial.println("Init Table A");
  InitOneSTrip(&stripSmartWine);
  /*
  mySerial.begin(19200);
  mySerial.println("Hello, world?");
  */
}

void loop()
{
  // we call the read function inside the loop
  artnet.readIt();
  /*
  String msg = smwSerial.getStrGeneral(colorSmartWine);
  
  Serial.print("Msg sent to SmartWine : ");
  Serial.println(msg);
  
  mySerial.println(msg);
  */
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
  
  //Serial.println("On DMX Frame !!!!!!!!!!!!!!!");
  
  // Table A ---
  setStripColor(&stripTableA, data[0], data[1], data[2]);
 // Table B ---
  setStripColor(&stripTableB, data[3], data[4], data[5]);
 // Table C ---
  setStripColor(&stripTableC, data[6], data[7], data[8]);
 // Table D ---
  setStripColor(&stripTableD, data[9], data[10], data[11]);
 // BackLight ---
  setStripColor(&stripBackLight, data[12], data[13], data[14]);
 // SmartWine ---
  setStripColor(&stripSmartWine, data[15], data[16], data[17]);
 
}

void InitOneSTrip(Adafruit_NeoPixel *strip) {
  
  strip->begin();

  setStripColor(strip, 0, 0, 0);
  delay(100);
  setStripColor(strip, 255, 0, 0);
  delay(100);
  setStripColor(strip, 0, 255, 0);
  delay(100);
  setStripColor(strip, 0, 0, 255);
  delay(100);
  
  setStripColor(strip, 255, 255, 255);
  delay(500);
  
}


/*****************************************************************
   Setting a strip to a specific color.
 *****************************************************************/
void setStripColor(Adafruit_NeoPixel * strip, int r, int g, int b) {
  for (int i = 0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, r, g, b);
  }
  strip->show();
}


