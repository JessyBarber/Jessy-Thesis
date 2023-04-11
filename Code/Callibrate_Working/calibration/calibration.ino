#include "calibration.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  double x_axis_data {};
  double y_axis_data {};
  double z_axis_data {};
  double x_axis_data_avg {};
  double y_axis_data_avg {};
  double z_axis_data_avg {};

  float scale = (float)sensitivity*calibration_n/vRef;
  float x_zero {};
  float y_zero {};
  float z_zero {};

  //Find average stationary offsets for each axis
  for (int i = 0; i < calibration_n; i++) {
    x_axis_data = analogRead(x_axis);
    y_axis_data = analogRead(y_axis);
    z_axis_data = analogRead(z_axis);

    x_axis_data_avg += x_axis_data;
    y_axis_data_avg += y_axis_data;
    z_axis_data_avg += z_axis_data;
  }

  x_axis_data_avg /= calibration_n;
  y_axis_data_avg /= calibration_n;
  z_axis_data_avg /= calibration_n;

  //Find the sensitivity for each axis
  x_zero = (x_axis_data_avg/(calibration_n-1)) * vRef;
  y_zero = (y_axis_data_avg/(calibration_n-1)) * vRef;
  z_zero = (z_axis_data_avg/(calibration_n-1)) * vRef;
  
  Serial.print("X zero: ");
  Serial.println(x_zero);
  Serial.print("Y zero: ");
  Serial.println(y_zero);
  Serial.print("Z zero: ");
  Serial.println(z_zero);

  // Serial.print("Avg x: ");
  // Serial.println(x_axis_data_avg);
  // Serial.print("Avg y: ");
  // Serial.println(y_axis_data_avg);
  // Serial.print("Avg z: ");
  // Serial.println(z_axis_data_avg);
}

void loop() {
  //PRINTING AND CHECKING ACCEL VALUES

  // double x_axis_data = analogRead(x_axis);
  // double y_axis_data = analogRead(y_axis);
  // double z_axis_data = analogRead(z_axis);
  // double x_zero = 0.42;
  // double y_zero = 0.41;
  // double z_zero = 0.50;

  // double xAccel = (x_axis_data * vRef / (calibration_n - 1) - x_zero);
  // double yAccel = (y_axis_data * vRef / (calibration_n - 1) - y_zero);
  // double zAccel = (z_axis_data * vRef / (calibration_n - 1) - z_zero);

  // Serial.print(xAccel);
  // Serial.print(" ");
  // Serial.print(yAccel);
  // Serial.print(" ");
  // Serial.println(zAccel);

  // Serial.print("X accel (g's): ");
  // Serial.print(xAccel, 2);
  // Serial.print(", Y accel (g's): ");
  // Serial.print(yAccel, 2);
  // Serial.print(", Z accel (g's)");
  // Serial.println(zAccel, 2);
  
  // delay(100);
}
