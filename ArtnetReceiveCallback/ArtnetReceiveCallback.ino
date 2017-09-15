/*
This is similar to ArtnetReceive but uses a callback to read the data.
This example may be copied under the terms of the MIT license, see the LICENSE file for details
*/

#include <Artnet.h>
#include <Ethernet2.h>
#include <EthernetUdp2.h>
#include <SPI.h>

Artnet artnet;

// Change ip and mac address for your setup
byte ip[] = {192, 168, 2, 16};
byte mac[] = {0x90, 0xA2, 0xDA, 0x11, 0x2F, 0x18};

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Hello World !");
  artnet.begin(mac, ip);
  
  // this will be called for each packet received
  artnet.setArtDmxCallback(onDmxFrame);
}

void loop()
{
  // we call the read function inside the loop
  artnet.readIt();
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
  Serial.println("On DMX Frame !!!!!!!!!!!!!!!");
  
  // print out our data
  Serial.print("universe number = ");
  Serial.print(universe);
  Serial.print("\tdata length = ");
  Serial.print(length);
  Serial.print("\tsequence n0. = ");
  Serial.println(sequence);
  Serial.print("DMX data: ");
  for (int i = 0 ; i < length ; i++)
  {
    Serial.print(data[i]);
    Serial.print("  ");
  }
  Serial.println();
  Serial.println();

}
