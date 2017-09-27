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

#define LED_PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, LED_PIN, NEO_GRB + NEO_KHZ800);
// ------------------------------------------------------------------------

// SERIAL SECTION ----------------------------------------------------------
#include "EC-SmartwineSerial.h"
#include "SoftwareSerial.h"

SmartwineSerial smwSerial;
// RX : 10
// TX : 11
SoftwareSerial mySerial(10, 11, true);
// ------------------------------------------------------------------------

uint32_t colorStrip = strip.Color(255, 255, 255);
uint32_t colorSmartWine = strip.Color(255, 000, 000);

void setup()
{
  Serial.begin(19200);
  Serial.println();
  Serial.println("Hello World !");
  artnet.begin(mac, ip);

  // this will be called for each packet received
  artnet.setArtDmxCallback(onDmxFrame);

  InitLeds();
  mySerial.begin(19200);
  //mySerial.println("Hello, world ?");
}

void InitLeds() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  delay(500);

  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
  delay(500);
  
}


void loop()
{
  // we call the read function inside the loop
  artnet.readIt();

  Serial.println(".");
    
  // To SmartWine
  String msg = smwSerial.getStrGeneral(colorSmartWine);
  Serial.print("Msg sent to SmartWine : ");
  Serial.println(msg);

  for(uint16_t i=0; i< msg.length(); i++) {
    mySerial.write(msg[i]);
    Serial.print(String(msg[i],HEX));
  }
  //mySerial.print(msg);

  delay(50);
  
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
  Serial.println("On DMX Frame !!!!!!!!!!!!!!!");
  colorStrip = strip.Color(data[0], data[1], data[2]);
  colorSmartWine = strip.Color(data[3], data[4], data[5]);

  // To the strip --
  for(uint16_t i=0; i< strip.numPixels(); i++) {
    strip.setPixelColor(i, colorStrip);
  }
  strip.show();
  
}
