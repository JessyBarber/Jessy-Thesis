#include "Sender.h"

double xZero = 0.0; double yZero = 0.0; double zZero = 0.0;

int Iterations = 150;

float max_accel_storage_x[sample_n]{}; float max_accel_storage_y[sample_n]{}; float max_accel_storage_z[sample_n]{};
float max_freq_storage_x[sample_n]{}; float max_freq_storage_y[sample_n]{}; float max_freq_storage_z[sample_n]{};

int count = 0;

void setup() {
  // //Initialise Serial connection
  Serial.begin(9600);
  LoRa.begin(915E6);
  callibrate(256, xZero, yZero, zZero);
}

void loop() {
  // ---------- VARIABLES ----------
  if(count < Iterations){
    // unsigned long StartTime = millis();
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
    checkNan(xFreq); 
    checkNan(yFreq);
    checkNan(zFreq);
    // ---------- CONVERT NAN TO 0 ----------

    max_accel_storage_x[count] = maxAccelX;
    max_accel_storage_y[count] = maxAccelY;
    max_accel_storage_z[count] = maxAccelZ;

    max_freq_storage_x[count] = xFreq;
    max_freq_storage_y[count] = yFreq;
    max_freq_storage_z[count] = zFreq;

    count ++;

    // unsigned long CurrentTime = millis();
    // unsigned long ElapsedTime = CurrentTime - StartTime;
    // Serial.println(ElapsedTime/1000);
  }
  else {
    count = 0;
    // for(int i = 0; i < sample_n; i++) {
    //   Serial.print(max_accel_storage_x[i]);
    //   Serial.print(" ");
    //   Serial.print(max_accel_storage_y[i]);
    //   Serial.print(" ");
    //   Serial.print(max_accel_storage_z[i]);
    //   Serial.print(" ");
    //   Serial.print(max_freq_storage_x[i]);
    //   Serial.print(" ");
    //   Serial.print(max_freq_storage_y[i]);
    //   Serial.print(" ");
    //   Serial.println(max_freq_storage_z[i]);
    // }

    float max_accel_x = findMax(max_accel_storage_x);
    float max_accel_y = findMax(max_accel_storage_y);
    float max_accel_z = findMax(max_accel_storage_z);

    float max_freq_x = findMax(max_freq_storage_x);
    float max_freq_y = findMax(max_freq_storage_y);
    float max_freq_z = findMax(max_freq_storage_z);

    Serial.print(max_accel_x);
    Serial.print(" ");
    Serial.print(max_accel_y);
    Serial.print(" ");
    Serial.print(max_accel_z);
    Serial.print(" ");
    Serial.print(max_freq_x);
    Serial.print(" ");
    Serial.print(max_freq_y);
    Serial.print(" ");
    Serial.println(max_freq_z);
  }

  // IF COUNT IS~~~~~~~~
  // ---------- TRANSMIT LORA PACKET ----------
  // LoRa.beginPacket();
  // LoRa.write((uint8_t*)&xFreq, sizeof(xFreq));
  // LoRa.write((uint8_t*)&yFreq, sizeof(yFreq));  
  // LoRa.write((uint8_t*)&zFreq, sizeof(zFreq));

  // LoRa.write((uint8_t*)&maxAccelX, sizeof(maxAccelX));
  // LoRa.write((uint8_t*)&maxAccelY, sizeof(maxAccelY));
  // LoRa.write((uint8_t*)&maxAccelZ, sizeof(maxAccelZ));
  // LoRa.endPacket();
  // ---------- TRANSMIT LORA PACKET ----------

}