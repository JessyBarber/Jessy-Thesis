#include "Sender.h"

double xZero = 0.0; double yZero = 0.0; double zZero = 0.0;

void setup() {
  // //Initialise Serial connection
  Serial.begin(9600);
  LoRa.begin(915E6);
  callibrate(256, xZero, yZero, zZero);
}

void loop() {
  // ---------- VARIABLES ----------
  // FFT SAMPLING
  double real_x_axis[sample_n]{}; double imag_x_axis[sample_n]{};
  double real_y_axis[sample_n]{}; double imag_y_axis[sample_n]{};
  double real_z_axis[sample_n]{}; double imag_z_axis[sample_n]{};
  
  // ACCELERATION SAMPLING
  double xAccel[sample_n]{}; double yAccel[sample_n]{}; double zAccel[sample_n]{};

  // VELOCITY SAMPLING
  double xVel[sample_n]{}; double yVel[sample_n]{}; double zVel[sample_n]{};

  // DISPLACEMENT SAMPLING
  double xDisp[sample_n]{}; double yDisp[sample_n]{}; double zDisp[sample_n]{};

  // MAXIMUM ACCELERATION
  double maxAccelX = 0.0; double maxAccelY = 0.0; double maxAccelZ = 0.0;

  // MAXIMUM DISPLACEMENT
  double maxDispX = 0.0; double maxDispY = 0.0; double maxDispZ = 0.0;

  // MAXIMUM FREQUENCY
  double xFreq = 0.0; double yFreq = 0.0; double zFreq = 0.0;
  // ---------- VARIABLES ----------

  // ---------- SAMPLE RAW DATA ----------
  readRawData(real_x_axis, real_y_axis, real_z_axis);
  // ---------- SAMPLE RAW DATA ----------

  // ---------- TURN RAW DATA INTO ACCELERATION (m/s/s) ----------
  processRawData(xAccel, yAccel, zAccel, real_x_axis, real_y_axis, real_z_axis,
                 xZero, yZero, zZero);
  // ---------- TURN RAW DATA INTO ACCELERATION (m/s/s) ----------

  // ---------- REMOVE DC BIAS ----------
  // removeBias(xAccel);
  // removeBias(yAccel);
  // removeBias(zAccel);
  // ---------- REMOVE DC BIAS ----------

  // ---------- REMOVE HIGH FREQUENCIES ----------
  lowPassFilter(xAccel, 0.1);
  lowPassFilter(yAccel, 0.1);
  lowPassFilter(zAccel, 0.1);
  // ---------- REMOVE HIGH FREQUENCIES ----------

  // ---------- SERIAL PRINT ACCELERATION (m/s/s) ----------
  printAxisValues(xAccel, yAccel, zAccel);
  // ---------- SERIAL PRINT ACCELERATION (m/s/s) ----------

  // ---------- FIND MAX ACCELERATION ----------
  maxAccelX = findMaxAbs(xAccel);
  maxAccelY = findMaxAbs(yAccel);
  maxAccelZ = findMaxAbs(zAccel);
  // ---------- FIND MAX ACCELERATION ----------

  // ---------- CALCULATE VELOCITY ----------
  // integrate(xAccel, yAccel, zAccel, xVel, yVel, zVel);
  // ---------- CALCULATE VELOCITY ----------

  // ---------- REMOVE VELOCITY DRIFT ----------
  // removeBias(xVel);
  // removeBias(yVel);
  // removeBias(zVel);
  // ---------- REMOVE VELOCITY DRIFT ----------

  // ---------- CALCULATE DISPLACEMENT ----------
  // integrate(xVel, yVel, zVel, xDisp, yDisp, zDisp);
  // ---------- CALCULATE DISPLACEMENT ----------

  // ---------- FIND MAX DISPLACEMENT ----------
  // maxDispX = findMaxAbs(xDisp);
  // maxDispY = findMaxAbs(yDisp);
  // maxDispZ = findMaxAbs(zDisp);
  // ---------- FIND MAX DISPLACEMENT ----------

  // ---------- TEST FUNCTIONS ----------
  // genSineWave(xAccel);
  // genSineWave(yAccel);
  // genSineWave(zAccel);
  // genZeroWave(xAccel);
  // genZeroWave(yAccel);
  // genZeroWave(zAccel);
  // ---------- TEST FUNCTIONS ----------

  // ---------- SERIAL PRINT MAX ACCELERATION (m/s/s) ----------
  // printAxisVal(maxAccelX, maxAccelY, maxAccelZ);
  // ---------- SERIAL PRINT ACCELERATION (m/s/s) ----------

  // ---------- SERIAL PRINT MAX DISPLACEMENT (m) ----------
  // printAxisVal(maxDispX, maxDispY, maxDispZ);
  // ---------- SERIAL PRINT MAX ACCELERATION (m/s/s) ----------

  // ---------- SERIAL PRINT VELOCITY (m/s) ----------
  // printAxisValues(xVel, yVel, zVel);
  // ---------- SERIAL PRINT ACCELERATION (m/s) ----------
  // delay(1000);
  // ---------- SERIAL PRINT DISPLACEMENT (m) ----------
  // printAxisValues(xDisp, yDisp, zDisp);
  // ---------- SERIAL PRINT DISPLACEMENT (m) ----------

  // ---------- COMPUTE FFT ----------
  arduinoFFT xFFT(xAccel, imag_x_axis, sample_n, sampling_rate);
  arduinoFFT yFFT(yAccel, imag_y_axis, sample_n, sampling_rate);
  arduinoFFT zFFT(zAccel, imag_z_axis, sample_n, sampling_rate);

  xFFT.Windowing(window_type, FFT_dir);
  yFFT.Windowing(window_type, FFT_dir);
  zFFT.Windowing(window_type, FFT_dir);

  xFFT.Compute(FFT_dir);
  yFFT.Compute(FFT_dir);
  zFFT.Compute(FFT_dir);

  xFFT.ComplexToMagnitude();
  yFFT.ComplexToMagnitude();
  zFFT.ComplexToMagnitude();
  // ---------- COMPUTE FFT ----------

  // ---------- FIND HIGHEST FREQUENCY ----------
  xFreq = xFFT.MajorPeak();
  yFreq = yFFT.MajorPeak();
  zFreq = zFFT.MajorPeak();
  // ---------- FIND HIGHEST FREQUENCY ----------

  // ---------- CONVERT NAN TO 0 ----------
  checkNan(xFreq);
  checkNan(yFreq);
  checkNan(zFreq);
  // ---------- CONVERT NAN TO 0 ----------

  // ---------- SERIAL PRINT FREQUENCY ----------
  // printAxisFreq(xFreq, yFreq, zFreq);
  // ---------- SERIAL PRINT FREQUENCY ----------

 // ---------- TRANSMIT LORA PACKET ----------
  LoRa.beginPacket();
  LoRa.write((uint8_t*)&xFreq, sizeof(xFreq));
  LoRa.write((uint8_t*)&yFreq, sizeof(yFreq));  
  LoRa.write((uint8_t*)&zFreq, sizeof(zFreq));

  // LoRa.write((uint8_t*)&maxDispX, sizeof(maxDispX));
  // LoRa.write((uint8_t*)&maxDispY, sizeof(maxDispY));
  // LoRa.write((uint8_t*)&maxDispZ, sizeof(maxDispZ));

  LoRa.write((uint8_t*)&maxAccelX, sizeof(maxAccelX));
  LoRa.write((uint8_t*)&maxAccelY, sizeof(maxAccelY));
  LoRa.write((uint8_t*)&maxAccelZ, sizeof(maxAccelZ));

  LoRa.endPacket();
  // ---------- TRANSMIT LORA PACKET ----------

  // delay(10000);
}