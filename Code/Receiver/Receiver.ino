#include <MKRWAN.h>

LoRaModem LoRa;

// LoRa settings
#define LORA_BAND    915E6  // frequency band
#define LORA_SF      7       // spreading factor
#define LORA_CR      5       // coding rate

namespace TNN {
  static const
}

void setup() {
  // initialize the LoRa modem
  LoRaModem.begin(LORA_BAND);
  LoRaModem.setSpreadingFactor(LORA_SF);
  LoRaModem.setCodingRate4(LORA_CR);
  
  // wait for the module to join the network
  while (!LoRaModem.isJoined()) {
    delay(10000);
  }
}

void loop() {
  // do something with received packets
}