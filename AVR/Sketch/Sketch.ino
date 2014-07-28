#include <PN532.h>
#include <SPI.h>
 
/*
 * Corrected MISO/MOSI/SCK for Mega from Jonathan Hogg (www.jonathanhogg.com)
 * SS is the same, due to NFC Shield schematic
 */


PN532 nfc(10);
 
void setup(void)
{
  Serial.begin(9600);
  nfc.begin();
  
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata)
  {
    Serial.print("Didn't find PN53x board");
    while (1);
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  Serial.print("Supports "); Serial.println(versiondata & 0xFF, HEX);
 
  nfc.SAMConfig();
}
 
 
void loop(void)
{
  uint32_t id;
  // look for MiFare type cards
  id = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A);
 
  if (id != 0)
  {
    Serial.print("Read card #"); Serial.println(id);
  }
}
