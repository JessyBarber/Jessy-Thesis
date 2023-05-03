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
    double receivedFreqX;
    double receivedFreqY;
    double receivedFreqZ;

    double receviedAccelX;
    double receviedAccelY;
    double receviedAccelZ;

    // double receivedDispX;
    // double receivedDispY;
    // double receivedDispZ;

    LoRa.readBytes((uint8_t*)&receivedFreqX, sizeof(receivedFreqX));
    LoRa.readBytes((uint8_t*)&receivedFreqY, sizeof(receivedFreqY));
    LoRa.readBytes((uint8_t*)&receivedFreqZ, sizeof(receivedFreqZ));

    // LoRa.readBytes((uint8_t*)&receivedDispX, sizeof(receivedDispX));
    // LoRa.readBytes((uint8_t*)&receivedDispY, sizeof(receivedDispY));
    // LoRa.readBytes((uint8_t*)&receivedDispZ, sizeof(receivedDispZ));

    LoRa.readBytes((uint8_t*)&receviedAccelX, sizeof(receviedAccelX));
    LoRa.readBytes((uint8_t*)&receviedAccelY, sizeof(receviedAccelY));
    LoRa.readBytes((uint8_t*)&receviedAccelZ, sizeof(receviedAccelZ));

    Serial.print(receivedFreqX); 
    Serial.print(" ");
    Serial.print(receivedFreqY);
    Serial.print(" ");
    Serial.print(receivedFreqZ);       
    // Serial.print(receivedDispX); 
    // Serial.print(" ");
    // Serial.print(receivedDispY);
    // Serial.print(" ");
    // Serial.print(receivedDispZ);

    Serial.print(" ");
    Serial.print(receviedAccelX); 
    Serial.print(" ");
    Serial.print(receviedAccelY);
    Serial.print(" ");
    Serial.println(receviedAccelZ);
  }
}