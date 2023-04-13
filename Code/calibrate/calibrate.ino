#include "calibrate.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // double x_axis_data {};
  // double y_axis_data {};
  // double z_axis_data {};
  // double x_axis_data_avg {};
  // double y_axis_data_avg {};
  // double z_axis_data_avg {};

  // // float scale = (float)sensitivity*calibration_n/vRef;
  // float x_zero {};
  // float y_zero {};
  // float z_zero {};

  // //Find average stationary offsets for each axis
  // for (int i = 0; i < samples; i++) {
  //   x_axis_data = analogRead(x_axis);
  //   y_axis_data = analogRead(y_axis);
  //   z_axis_data = analogRead(z_axis);

  //   x_axis_data_avg += x_axis_data;
  //   y_axis_data_avg += y_axis_data;
  //   z_axis_data_avg += z_axis_data;
  // }

  // x_axis_data_avg /= samples;
  // y_axis_data_avg /= samples;
  // z_axis_data_avg /= samples;
  // // x_zero = (x_axis_data_avg / sensitivity) * (adc_resolution / (2 * vRef));
  // // y_zero = (y_axis_data_avg / sensitivity) * (adc_resolution / (2 * vRef));
  // // z_zero = (z_axis_data_avg / sensitivity) * (adc_resolution / (2 * vRef));

  // //Find the sensitivity for each axis
  // x_zero = (x_axis_data_avg/(samples-1)) * vRef;
  // y_zero = (y_axis_data_avg/(samples-1)) * vRef;
  // z_zero = (z_axis_data_avg/(samples-1)) * vRef;
  
  // Serial.print("X zero: ");
  // Serial.println(x_zero);
  // Serial.print("Y zero: ");
  // Serial.println(y_zero);
  // Serial.print("Z zero: ");
  // Serial.println(z_zero);

  // // Serial.print("Avg x: ");
  // // Serial.println(x_axis_data_avg);
  // // Serial.print("Avg y: ");
  // // Serial.println(y_axis_data_avg);
  // // Serial.print("Avg z: ");
  // // Serial.println(z_axis_data_avg);

  Serial.println("Calibrating accelerometer...");

  long offsetX = 0;
  long offsetY = 0;
  long offsetZ = 0;

  for (int i = 0; i < samples; i++) {
    int rawX = analogRead(x_axis);
    int rawY = analogRead(y_axis);
    int rawZ = analogRead(z_axis);

    offsetX += rawX;
    offsetY += rawY;
    offsetZ += rawZ - (sensitivity * (adc_resolution / vRef)); // Assuming 1g on the Z-axis when the device is at rest
    delay(10); // Wait for 10 ms between samples
  }

  offsetX /= samples;
  offsetY /= samples;
  offsetZ /= samples;

  float voltageOffsetX = (offsetX * vRef) / (adc_resolution);
  float voltageOffsetY = (offsetY * vRef) / (adc_resolution);
  float voltageOffsetZ = (offsetZ * vRef) / (adc_resolution);

  Serial.print("Offset X: ");
  Serial.println(voltageOffsetX, 6);
  Serial.print("Offset Y: ");
  Serial.println(voltageOffsetY, 6);
  Serial.print("Offset Z: ");
  Serial.println(voltageOffsetZ, 6);

  delay(10000);
}
