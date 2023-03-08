#include <MKRWAN.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa Modem Started");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String frequencyString = "";
    while (LoRa.available()) {
      frequencyString += (char)LoRa.read();
    }
    double averageFrequency = frequencyString.toDouble();
    Serial.print("Received Average Frequency: ");
    Serial.println(averageFrequency);
  }
}
  
