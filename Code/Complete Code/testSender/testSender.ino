#include "Sender.h"

double xZero = 0.0; double yZero = 0.0; double zZero = 0.0;

float max_freq_x = 0.0; float max_freq_y = 0.0; float max_freq_z = 0.0;

float max_accel_x = 0.0; float max_accel_y = 0.0; float max_accel_z = 0.0;

unsigned long previousMillis = 0;
const long interval = 20000; //60 second interval (1 minute) 

void setup() {
  // //Initialise Serial connection
  Serial.begin(9600);
  LoRa.begin(915E6);
  callibrate(256, xZero, yZero, zZero);
}

void loop() {
  // ---------- VARIABLES ----------

  unsigned long currentMillis = millis();
  // FFT SAMPLING
  double real_x_axis[sample_n]{}; double imag_x_axis[sample_n]{};
  double real_y_axis[sample_n]{}; double imag_y_axis[sample_n]{};
  double real_z_axis[sample_n]{}; double imag_z_axis[sample_n]{};
  
  // ACCELERATION SAMPLING
  double xAccel[sample_n]{}; double yAccel[sample_n]{}; double zAccel[sample_n]{};

  // MAXIMUM ACCELERATION
  float maxAccelX = 0.0; float maxAccelY = 0.0; float maxAccelZ = 0.0;

  // MAXIMUM FREQUENCY
  float xFreq = 0.0; float yFreq = 0.0; float zFreq = 0.0;
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

  // ---------- SERIAL PRINT ACCELERATION (m/s/s) ----------
  // printAxisValues(xAccel, yAccel, zAccel);
  // ---------- SERIAL PRINT ACCELERATION (m/s/s) ----------

  // ---------- FIND MAX ACCELERATION ----------
  maxAccelX = float(findMaxAbs(xAccel));
  maxAccelY = float(findMaxAbs(yAccel));
  maxAccelZ = float(findMaxAbs(zAccel));
  // ---------- FIND MAX ACCELERATION ----------

  // ---------- REMOVE HIGH FREQUENCIES ----------
  // double alpha = 0.3827;
  // double alpha = 0.3394;
  lowPassFilter(xAccel);
  lowPassFilter(yAccel);
  lowPassFilter(zAccel);
  // ---------- REMOVE HIGH FREQUENCIES ----------

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
  xFreq = float(xFFT.MajorPeak());
  yFreq = float(yFFT.MajorPeak());
  zFreq = float(zFFT.MajorPeak());
  // ---------- FIND HIGHEST FREQUENCY ----------

  // ---------- CONVERT NAN TO 0 ----------
  checkNan(maxAccelX); 
  Serial.print("max accel x");
  Serial.println(maxAccelX);
  checkNan(maxAccelY);
  checkNan(maxAccelZ);
  // ---------- CONVERT NAN TO 0 ----------

  // ---------- CONVERT NAN TO 0 ----------
  checkNan(xFreq); 
  checkNan(yFreq);
  checkNan(zFreq);
  // ---------- CONVERT NAN TO 0 ----------


  if (xFreq > max_freq_x) {
    max_freq_x = xFreq;
  }
  if (yFreq > max_freq_y) {
    max_freq_y = yFreq;
  }
  if (zFreq > max_freq_z) {
    max_freq_z = zFreq;
  }
  if (maxAccelX > max_accel_x) {
    max_accel_x = maxAccelX;
  }
  if (maxAccelY > max_accel_y) {
    max_accel_y = maxAccelY;
  }
  if (maxAccelZ > max_accel_z) {
    max_accel_z = maxAccelZ;
  }
  Serial.println(currentMillis);
  //Reset the max values
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    LoRa.beginPacket();
    LoRa.write((uint8_t*)&max_freq_x, sizeof(max_freq_x));
    LoRa.write((uint8_t*)&max_freq_y, sizeof(max_freq_y));
    LoRa.write((uint8_t*)&max_freq_z, sizeof(max_freq_z));
    LoRa.write((uint8_t*)&max_accel_x, sizeof(max_accel_x));
    LoRa.write((uint8_t*)&max_accel_y, sizeof(max_accel_y));
    LoRa.write((uint8_t*)&max_accel_z, sizeof(max_accel_z));
    LoRa.endPacket();
    
    max_freq_x = 0.0; 
    max_freq_y = 0.0; 
    max_freq_z = 0.0;
    max_accel_x = 0.0;
    max_accel_y = 0.0; 
    max_accel_z = 0.0;
  }
}