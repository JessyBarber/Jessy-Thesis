#include <MKRWAN.h>
#include "Arduino.h"

LoRaModem modem;

String appEui = "F5F8685554F87B5A";
String appKey = "78474767344737693633517962384F50";

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  if (!modem.begin(AU915)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  int connected;
  connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }

  // float xFreq = 1.0;
  // float yFreq = 2.0;
  // float zFreq = 3.0;

  int err;
  modem.setPort(3);
  modem.beginPacket();
  // modem.write((uint8_t*)&xFreq, sizeof(xFreq));
  modem.write("HeLoRa World!");
  // modem.write((uint8_t*)&yFreq, sizeof(yFreq));  
  // modem.write((uint8_t*)&zFreq, sizeof(zFreq));
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}