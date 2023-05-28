#include "Sender.h"

double xZero = 0.0; double yZero = 0.0; double zZero = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LoRa.begin(915E6);
  callibrate(256, xZero, yZero, zZero);
}

void loop() {
  // // put your main code here, to run repeatedly:
  // // ---------- VARIABLES ----------
  // // FFT SAMPLING
  // double real_x_axis[sample_n]{}; double imag_x_axis[sample_n]{};
  // double real_y_axis[sample_n]{}; double imag_y_axis[sample_n]{};
  // double real_z_axis[sample_n]{}; double imag_z_axis[sample_n]{};
  
  // // ACCELERATION SAMPLING
  // double xAccel[sample_n]{}; double yAccel[sample_n]{}; double zAccel[sample_n]{};

  // // MAXIMUM ACCELERATION
  // float maxAccelX = 0.0; float maxAccelY = 0.0; float maxAccelZ = 0.0;

  // // MAXIMUM FREQUENCY
  // float xFreq = 0.0; float yFreq = 0.0; float zFreq = 0.0;
  // // ---------- VARIABLES ----------

  // // ---------- SAMPLE RAW DATA ----------
  // readRawData(real_x_axis, real_y_axis, real_z_axis);
  // // ---------- SAMPLE RAW DATA ----------
  
  // // ---------- TURN RAW DATA INTO ACCELERATION (m/s/s) ----------
  // processRawData(xAccel, yAccel, zAccel, real_x_axis, real_y_axis, real_z_axis,
  //                xZero, yZero, zZero);
  // // ---------- TURN RAW DATA INTO ACCELERATION (m/s/s) ----------s

  //  // ---------- SERIAL PRINT ACCELERATION (m/s/s) ----------
  // printAxisValues(xAccel, yAccel, zAccel);
  // // ---------- SERIAL PRINT ACCELERATION (m/s/s) ----------

  // // ---------- FIND MAX ACCELERATION ----------
  // maxAccelX = float(findMaxAbs(xAccel));
  // maxAccelY = float(findMaxAbs(yAccel));
  // maxAccelZ = float(findMaxAbs(zAccel));
  // // ---------- FIND MAX ACCELERATION ----------

  // // ---------- REMOVE HIGH FREQUENCIES ----------
  // // double alpha = 0.3827;
  // // double alpha = 0.3394;
  // lowPassFilter(xAccel);
  // lowPassFilter(yAccel);
  // lowPassFilter(zAccel);
  // // ---------- REMOVE HIGH FREQUENCIES ----------

  // // ---------- COMPUTE FFT ----------
  // arduinoFFT xFFT(xAccel, imag_x_axis, sample_n, sampling_rate);
  // arduinoFFT yFFT(yAccel, imag_y_axis, sample_n, sampling_rate);
  // arduinoFFT zFFT(zAccel, imag_z_axis, sample_n, sampling_rate);

  // xFFT.Windowing(window_type, FFT_dir);
  // yFFT.Windowing(window_type, FFT_dir);
  // zFFT.Windowing(window_type, FFT_dir);

  // xFFT.Compute(FFT_dir);
  // yFFT.Compute(FFT_dir);
  // zFFT.Compute(FFT_dir);

  // xFFT.ComplexToMagnitude();
  // yFFT.ComplexToMagnitude();
  // zFFT.ComplexToMagnitude();
  // // ---------- COMPUTE FFT ----------

  // // ---------- FIND HIGHEST FREQUENCY ----------
  // xFreq = float(xFFT.MajorPeak());
  // yFreq = float(yFFT.MajorPeak());
  // zFreq = float(zFFT.MajorPeak());
  // // ---------- FIND HIGHEST FREQUENCY ----------

  // // ---------- CONVERT NAN TO 0 ----------
  // checkNan(xFreq); 
  // checkNan(yFreq);
  // checkNan(zFreq);
  // // ---------- CONVERT NAN TO 0 ----------
}
