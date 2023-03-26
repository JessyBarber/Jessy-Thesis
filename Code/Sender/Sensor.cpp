#include "Sender.h"
// LoRaModem LoRa;

// namespace TNN {
// static const char DEV_EUI[] = "70B3D57ED005BBA1";
// static const char APP_EUI[] = "323738316A377F09";
// static const char APP_KEY[] = "E863410BB8DC8ED66D23285FBD231518";
// }

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   while (!Serial);
//   Serial.println("here1");
//   bool beginSuccess = LoRa.begin(AU915);
//   if(beginSuccess){
//     Serial.println("Success to start modem");
//   } else{
//     Serial.println("Failed to start modem");
//   }

//   // if(!LoRa.begin(AU915)){
//   //   Serial.println("Failed to start modem");
//   //   while(true);
//   // }
//   Serial.println("here2");
//   bool joinSuccess = LoRa.joinOTAA(TNN::APP_EUI, TNN::APP_KEY, TNN::DEV_EUI);
//   if (joinSuccess) {
//       Serial.println("Joined successfully");
//   } else {
//       Serial.println("Join failed");
//   }
//   Serial.println("here3");
// }

int readAxis(int axis){
  return analogRead(axis);
}

void printAxis(char label, int axis){
  // Serial.println("%c = %d",&label, readAxis(axis));
  Serial.print(label);
  Serial.print("= \t");
  Serial.println(readAxis(axis));
  // Serial.print("\t");
}