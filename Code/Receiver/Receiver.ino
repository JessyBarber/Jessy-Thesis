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
  // int packetSize = LoRa.parsePacket();
  // if (packetSize) {
  //   byte buffer[1100];
  //   // double buffer[sample_n * sizeof(double)];
  //   // int len = LoRa.readBytes(buffer, sizeof(buffer));
  //   // double data[sample_n];
  //   // memcpy(data, &buffer, sizeof(data));

  //   // Serial.print("Received Data: ");
  //   // for (int i = 0; i < sizeof(data) / sizeof(double); i++) {
  //   //   Serial.print(data[i]);
  //   //   Serial.print(" ");
  //   // }
  //   // Serial.println();
  //   Serial.print("Received packet of size ");
  //   Serial.println(packetSize);
  //   for (int i = 0; i < packetSize; i++) {
  //     buffer[i] = LoRa.read();
  //   }

  //   int numDoubles = packetSize / sizeof(double);
  //   double decoded[numDoubles];
  //   memcpy(&decoded, buffer, packetSize);

  //   for (int i = 0; i < numDoubles; i++) {
  //     Serial.println(decoded[i]);
  //   }

  // delay(1000);
// }





  // //Retrieve the packet size 
  // int packetSize = LoRa.parsePacket();
  // if (packetSize) {
  //   String frequencyString = "";
  //   while(LoRa.available()) {
  //     frequencyString += (char)LoRa.read();
  //   }
  //   double averageFreq = frequencyString.toDouble();
  //   Serial.print("Received Average Frequency: ");
  //   Serial.println(averageFreq);
  // }
// }