#include "Sender.h"

void setup() {
  // //Initialise Serial connection
  // Serial.begin(9600);
  // while (!Serial)
  //   ;
  // Serial.println("Starting Serial Success");
  // //Initialise LoRa connection
  // if (!LoRa.begin(915E6)) {
  //   Serial.println("Starting LoRa failed!");
  //   while (1)
  //     ;
  // }
  // Serial.println("LoRa Modem Started");
  //Initialise LoRa connection
  LoRa.begin(915E6);
  // LoRa.setFrequency(915E6);
}

void loop() {
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

  // long int t1 = millis();
  //SAMPLE RAW DATA
  for (int i = 0; i < sample_n; i++) {
    real_x_axis[i] = analogRead(x_axis);
    real_y_axis[i] = analogRead(y_axis);
    real_z_axis[i] = analogRead(z_axis);
    delay(sample_interval);
  }
  // long int t2 = millis();
  // Serial.print("Time taken: "); Serial.print((t2-t1)/1000); Serial.println(" s");

  //-------------------- DEBUGGING --------------------
  //-------------------- DEBUGGING --------------------

  //SAMPLE ACCEL DATA
  for (int i = 0; i < sample_n; i++) {
    // xAccel[i] = (real_x_axis[i] * vRef / (adc_resolution - 1) - x_zero);
    // yAccel[i] = (real_y_axis[i] * vRef / (adc_resolution - 1) - y_zero);
    // zAccel[i] = (real_z_axis[i] * vRef / (adc_resolution - 1) - z_zero);

    double voltageX = real_x_axis[i] * vRef / (adc_resolution - 1);
    double voltageY = real_y_axis[i] * vRef / (adc_resolution - 1);
    double voltageZ = real_z_axis[i] * vRef / (adc_resolution - 1);

    xAccel[i] = (voltageX - x_zero) / sensitivity;
    yAccel[i] = (voltageY - y_zero) / sensitivity;
    zAccel[i] = ((voltageZ - z_zero) / sensitivity) - 1.0; // subtract Earth's gravity
  }

  // // PRINT RAW ACCEL VALUES
  // for (int i = 0; i < sample_n; i++) {
  //   Serial.print(xAccel[i]);
  //   Serial.print(" ");
  //   Serial.print(yAccel[i]);
  //   Serial.print(" ");
  //   Serial.println(zAccel[i]);
  // }

  //FIND AND PRINT MAX ACCEL VALS
  double maxXAccel = findMax(xAccel);
  double maxYAccel = findMax(yAccel);
  double maxZAccel = findMax(zAccel);

  // Serial.print(maxXAccel);
  // Serial.print(" ");
  // Serial.print(maxYAccel);
  // Serial.print(" ");
  // Serial.println(maxZAccel);

  //DEMEAN DATA -> NOT USED
  // deMean(real_x_axis);
  // deMean(real_y_axis);
  // deMean(real_z_axis);

  // ---------- UNDER CONSTRUCTION ----------
  // // Lowpass filter
  // double filteredXAccel[sample_n] {};
  // double filteredYAccel[sample_n] {};
  // double filteredZAccel[sample_n] {};

  // int filterWindowSize = 5; // Adjust this value based on the noise characteristics of your signal

  // lowPassFilter(xAccel, filteredXAccel, filterWindowSize);
  // lowPassFilter(yAccel, filteredYAccel, filterWindowSize);
  // lowPassFilter(zAccel, filteredZAccel, filterWindowSize);
  // ---------- UNDER CONSTRUCTION ----------

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

  // //PRINT ALL FFT VALS -> FOR PLOTTING FFT PEAKS
  // for (int i = 0; i < sample_n; i++) {
  //   Serial.print(xAccel[i]);
  //   Serial.print(" ");
  //   Serial.print(yAccel[i]);
  //   Serial.print(" ");
  //   Serial.println(zAccel[i]);
  // }

  // //PRINTING MAX FFTS VALS
  // Serial.print(findMax(xAccel));
  // Serial.print(" ");
  // Serial.print(findMax(yAccel));
  // Serial.print(" ");
  // Serial.println(findMax(zAccel));

  // ---------- UNDER CONSTRUCTION ----------
  // // CONVERTING MAX INDEX TO ACTUAL FREQ
  // double threshold = 0.2;
  // int maxIndexX = findMaxIndex(xAccel, threshold);
  // int maxIndexY = findMaxIndex(yAccel, threshold);
  // int maxIndexZ = findMaxIndex(zAccel, threshold);

  int maxIndexX = findMaxIndex(xAccel);
  int maxIndexY = findMaxIndex(yAccel);
  int maxIndexZ = findMaxIndex(zAccel);

  double frequencyX = maxIndexX * ((double)sample_rate / sample_n);
  double frequencyY = maxIndexY * ((double)sample_rate / sample_n);
  double frequencyZ = maxIndexZ * ((double)sample_rate / sample_n);

  Serial.print("Frequency X: ");
  Serial.println(frequencyX);
  Serial.print("Frequency Y: ");
  Serial.println(frequencyY);
  Serial.print("Frequency Z: ");
  Serial.println(frequencyZ);

  // Serial.print(frequencyX);
  // Serial.print(" ");
  // Serial.print(frequencyY);
  // Serial.print(" ");
  // Serial.println(frequencyZ);


  // ---------- UNDER CONSTRUCTION ----------

  // //SEND DATA PACKETS 
  // double data1 = findMax(xAccel);
  // double data2 = findMax(yAccel);
  // double data3 = findMax(zAccel);

  // uint8_t bytes[sizeof(real_x_axis)];
  // for (int i = 0; i < sizeof(real_x_axis); i += sizeof(double)) {
  //   double val = real_x_axis[i / sizeof(double)];
  //   memcpy(&bytes[i], &val, sizeof(double));
  // }

  //TRANSMIT LORA PACKET
  LoRa.beginPacket();
  // LoRa.write(buffer, packetSize);
  LoRa.write((uint8_t*)&frequencyX, sizeof(frequencyX));
  LoRa.write((uint8_t*)&frequencyY, sizeof(frequencyY));  
  LoRa.write((uint8_t*)&frequencyZ, sizeof(frequencyZ));
  LoRa.endPacket();

  // delay(10000);
}