/*
  Lora Send And Receive
  This sketch demonstrates how to send and receive data with the MKR WAN 1300/1310 LoRa module.
  This example code is in the public domain.
*/

#include <MKRWAN.h>
#include <cstring>

LoRaModem modem;

// Uncomment if using the Murata chip as a module
// LoRaModem modem(Serial1);

// #include "arduino_secrets.h"
// Please enter your sensitive data in the Secret tab or arduino_secrets.h
// String appEui = SECRET_APP_EUI;
// String appKey = SECRET_APP_KEY;

String devAddr = "260D6AA9";
String nwkSKey = "C9B75B5F1C710C7D8BC4E8DB99A1DAF9";
String appSKey = "A4B7EE8940BD741C05186B3BA46FDD50";
String appEui = "f5f8685554f87b5a";
String appKey = "764b3832644a64537571556e74435a33";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(AU915)) {
    Serial.println("Failed to start module");
    while (1) {}
  };

  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());
  modem.sendMask("ff000001f000ffff00020000");
  Serial.println(modem.getChannelMask());
  modem.setADR(true);

  // Serial.println("Attempting to set private network mode");
  // if (!modem.publicNetwork(false)) {
  //   Serial.println("Failed to set private network mode");
  //   while(1){}
  // }
  // Serial.println("Successfully set private network mode");

  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }
  else {
    Serial.println("Connection Successful");
  }

  // Set poll interval to 30 secs.
  modem.minPollInterval(30);
  // NOTE: independent of this setting, the modem will
  // not allow sending more than one message every 2 minutes,
  // this is enforced by firmware and can not be changed.
  delay(10000);
}

void loop() {
  int err;

  float val1 = 2.0;
  float val2 = 3.0;

  unsigned char bytes1[sizeof(float)];
  unsigned char bytes2[sizeof(float)];

  std::memcpy(bytes1, &val1, sizeof(float));
  std::memcpy(bytes2, &val2, sizeof(float));

  modem.beginPacket();
  modem.write(bytes1, sizeof(bytes1));
  modem.write(bytes2, sizeof(bytes2));
  err = modem.endPacket(false); //True means send downlink false means don't

  delay(100000);
}