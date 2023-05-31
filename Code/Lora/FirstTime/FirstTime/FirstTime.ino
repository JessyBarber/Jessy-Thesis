#include <MKRWAN.h>
LoRaModem modem;
// Please enter your sensitive data in the Secret tab or arduino_secrets.h
String appEui = "F5F8685554F87B5A";
String appKey = "78474767344737693633517962384F50";

void setup() {
  Serial.begin(9600);
  // while (!Serial);
  Serial.print("Attempting to connect to network");
  if (!modem.begin(AU915)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  delay(5000);
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());
  modem.sendMask("ff000001f000ffff00020000");
  Serial.println(modem.getChannelMask());
  modem.setADR(true);
  // join();
  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry. Retrying");
  }
  else {
    Serial.println("Connection Successful");
  }
  // Set poll interval to 30 secs.
  modem.minPollInterval(30);
}

// void join() {
//   int connected = modem.joinOTAA(appEui, appKey);
//   if (!connected) {
//     Serial.println("Something went wrong; are you indoor? Move near a window and retry. Retrying");
//     join();
//   }
// }
void loop(){
}