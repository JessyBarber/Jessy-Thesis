#include "plotter.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // //PRINTING ANALOG SERIAL RAW DATA
  // double x_axis_data = analogRead(x_axis);
  // double y_axis_data = analogRead(y_axis);
  // double z_axis_data = analogRead(z_axis);
  // Serial.print(x_axis_data);
  // Serial.print(" ");
  // Serial.print(y_axis_data);
  // Serial.print(" ");
  // Serial.println(z_axis_data);
  // delay(1000);

  //FFT SAMPLING
  double real_x_axis[sample_n]{};
  double imag_x_axis[sample_n]{};
  double real_y_axis[sample_n]{};
  double imag_y_axis[sample_n]{};
  double real_z_axis[sample_n]{};
  double imag_z_axis[sample_n]{};
  
  //ACCEL SAMPLING
  double xAccel[sample_n] {};
  double yAccel[sample_n] {};
  double zAccel[sample_n] {};
  
  //SAMPLE RAW DATA
  for (int i = 0; i < sample_n; i++) {
    real_x_axis[i] = analogRead(x_axis);
    real_y_axis[i] = analogRead(y_axis);
    real_z_axis[i] = analogRead(z_axis);
    delayMicroseconds(1000 / sample_rate);
  }

  //SAMPLE ACCEL DATA
  for (int i = 0; i < sample_n; i++) {
    xAccel[i] = (real_x_axis[i] * vRef / (adc_resolution - 1) - x_zero);
    yAccel[i] = (real_y_axis[i] * vRef / (adc_resolution - 1) - y_zero);
    zAccel[i] = (real_z_axis[i] * vRef / (adc_resolution - 1) - z_zero);
  }

  // //PRINTING MAX ACCEL VALS
  // Serial.print(findMax(xAccel));
  // Serial.print(" ");
  // Serial.print(findMax(yAccel));
  // Serial.print(" ");
  // Serial.println(findMax(zAccel));

  //DEMEAN FOR FFT NOT SURE IF I STILL NEED THIS (WAS TO GET RID OF PEAK AT 0HZ WHEN I WAS USING RAW DATA)
  // deMean(real_x_axis);
  // deMean(real_y_axis);
  // deMean(real_z_axis);
  
  //COMPUTE FFT
  arduinoFFT xFFT(xAccel, imag_x_axis, sample_n, sample_rate);
  arduinoFFT yFFT(yAccel, imag_y_axis, sample_n, sample_rate);
  arduinoFFT zFFT(zAccel, imag_z_axis, sample_n, sample_rate);

  xFFT.Windowing(window_type, FFT_dir);
  yFFT.Windowing(window_type, FFT_dir);
  zFFT.Windowing(window_type, FFT_dir);

  xFFT.Compute(FFT_dir);
  yFFT.Compute(FFT_dir);
  zFFT.Compute(FFT_dir);

  xFFT.ComplexToMagnitude();
  yFFT.ComplexToMagnitude();
  zFFT.ComplexToMagnitude();

  //PRINTING MAX FFTS VALS
  Serial.print(findMax(xAccel));
  Serial.print(" ");
  Serial.print(findMax(yAccel));
  Serial.print(" ");
  Serial.println(findMax(zAccel));
  

  // Serial.println("break-------------------");
  // for (int i = 0; i < sample_n; i++) {
  //   Serial.print(real_x_axis[i]);
  //   Serial.print(" ");
  //   Serial.print(real_y_axis[i]);
  //   Serial.print(" ");
  //   Serial.println(real_z_axis[i]);
  //   delay(100);
  // }
}