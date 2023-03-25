#include "Sender.h"

const int x_axis = A1;
#define SAMPLES 5

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Starting Serial Success");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.print(analogRead(x_axis));
  // Serial.print("\t");
  // Serial.print(analogRead(y_axis));
  // Serial.print("\t");
  // Serial.print(analogRead(z_axis));
  // Serial.println();
  // delay(100);
  // int x_data = readAxis(x_axis);
  // int y_data = readAxis(y_axis);
  // int z_data = readAxis(z_axis);
  // int16_t accelerometerDataX[SAMPLES]; // array to hold accelerometer X-axis data
  //   for (int i = 0; i < SAMPLES; i++) {
  //   accelerometerDataX[i] = analogRead(x_axis);
  //   delay(1000); // wait for sampling interval
  // }
  Serial.println(analogRead(x_axis));
  delay(500);

  // printAxis(readAxis(accelerometerDataX[0]));
  // printAxis(readAxis(y_axis));
  // printAxis(readAxis(z_axis));
  // Serial.println();
  delay(5000);
}