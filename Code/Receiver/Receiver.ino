#include "Receiver.h"

void setup() {
  //Initialise Serial connection
  Serial.begin(9600);
  //Initialise LoRa Connection
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Modem Started");
}

void loop() {
    if (LoRa.parsePacket()) {
    double receivedData1;
    double receivedData2;
    double receivedData3;

    LoRa.readBytes((uint8_t*)&receivedData1, sizeof(receivedData1));
    LoRa.readBytes((uint8_t*)&receivedData2, sizeof(receivedData2));
    LoRa.readBytes((uint8_t*)&receivedData3, sizeof(receivedData3));

    // Serial.print("Received Data: ");
    Serial.print(receivedData1); 
    Serial.print(" ");
    Serial.print(receivedData2);
    Serial.print(" ");
    Serial.println(receivedData3);
  }
}