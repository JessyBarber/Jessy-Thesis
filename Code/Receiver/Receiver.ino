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
  //Retrieve the packet size 
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String frequencyString = "";
    while(LoRa.available()) {
      frequencyString += (char)LoRa.read();
    }
    double averageFreq = frequencyString.toDouble();
    Serial.print("Received Average Frequency: ");
    Serial.println(averageFreq);
  }
}