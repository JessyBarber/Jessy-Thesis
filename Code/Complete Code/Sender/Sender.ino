#include "Sender.h"

double xZero = 0.0; double yZero = 0.0; double zZero = 0.0;

//Store total max values for averaging later
float totalMaxAccelX = 0.0; float totalMaxAccelY = 0.0; float totalMaxAccelZ = 0.0;
float totalMaxFreqX = 0.0; float totalMaxFreqY = 0.0; float totalMaxFreqZ = 0.0;
//Record the number of computations within the time limit
int computationCount = 0;
//Timing variables
unsigned long previousMillis = 0;
const long interval = 60000; //test scenario 60 seconds

void setup() {
  // //Initialise Serial connection
  Serial.begin(9600);
  LoRa.begin(915E6);
  callibrate(256, xZero, yZero, zZero);
}

void loop() {
  // ---------- VARIABLES ----------
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

  // ---------- SERIAL PRINT ACCELERATION (m/s/s) ----------
  // printAxisValues(xAccel, yAccel, zAccel);
  // ---------- SERIAL PRINT ACCELERATION (m/s/s) ----------

  // ---------- FIND MAX ACCELERATION ----------
  maxAccelX = float(findMaxAbs(xAccel));
  maxAccelY = float(findMaxAbs(yAccel));
  maxAccelZ = float(findMaxAbs(zAccel));
  // ---------- FIND MAX ACCELERATION ----------

  // ---------- REMOVE HIGH FREQUENCIES ----------
  lowPassFilter(xAccel);
  lowPassFilter(yAccel);
  lowPassFilter(zAccel);
  // ---------- REMOVE HIGH FREQUENCIES ----------

  // ---------- COMPUTE FFT ----------
  arduinoFFT xFFT(xAccel, imag_x_axis, sample_n, sampling_rate);
  arduinoFFT yFFT(yAccel, imag_y_axis, sample_n, sampling_rate);
  arduinoFFT zFFT(zAccel, imag_z_axis, sample_n, sampling_rate);

  xFFT.DCRemoval();
  yFFT.DCRemoval();
  zFFT.DCRemoval();

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
  // ---------- FIND HIGHEST FREQUENCY ----------x

  // ---------- CONVERT NAN TO 0 ----------
  checkNan(maxAccelX); 
  checkNan(maxAccelY);
  checkNan(maxAccelZ);

  checkNan(xFreq); 
  checkNan(yFreq);
  checkNan(zFreq);
  // ---------- CONVERT NAN TO 0 ----------

  totalMaxAccelX += maxAccelX;
  totalMaxAccelY += maxAccelY;
  totalMaxAccelZ += maxAccelZ;

  totalMaxFreqX += xFreq;
  totalMaxFreqY += yFreq;
  totalMaxFreqZ += zFreq;

  computationCount++;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float averageMaxAccelX = totalMaxAccelX / computationCount;
    float averageMaxAccelY = totalMaxAccelY / computationCount;
    float averageMaxAccelZ = totalMaxAccelZ / computationCount;

    float averageMaxFreqX = totalMaxFreqX / computationCount;
    float averageMaxFreqY = totalMaxFreqY / computationCount;
    float averageMaxFreqZ = totalMaxFreqZ / computationCount;

    Serial.print(averageMaxAccelX);
    Serial.print(" ");
    Serial.print(averageMaxAccelY);
    Serial.print(" ");
    Serial.print(averageMaxAccelZ);
    Serial.print(" ");
    Serial.print(averageMaxFreqX);
    Serial.print(" ");
    Serial.print(averageMaxFreqY);
    Serial.print(" ");
    Serial.println(averageMaxFreqZ);

    LoRa.beginPacket();
    LoRa.write((uint8_t*)&maxAccelX, sizeof(maxAccelX));
    LoRa.write((uint8_t*)&maxAccelY, sizeof(maxAccelY));
    LoRa.write((uint8_t*)&maxAccelZ, sizeof(maxAccelZ));

    LoRa.write((uint8_t*)&xFreq, sizeof(xFreq));
    LoRa.write((uint8_t*)&yFreq, sizeof(yFreq));  
    LoRa.write((uint8_t*)&zFreq, sizeof(zFreq));
    LoRa.endPacket();

    totalMaxAccelX = 0.0;
    totalMaxAccelY = 0.0;
    totalMaxAccelZ = 0.0;

    totalMaxFreqX = 0.0;
    totalMaxFreqY = 0.0;
    totalMaxFreqZ = 0.0;

    computationCount = 0;
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