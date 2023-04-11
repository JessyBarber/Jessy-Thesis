#include "Sender.h"

void setup() {
  //Initialise Serial connection
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("Starting Serial Success");
  //Initialise LoRa connection
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  Serial.println("LoRa Modem Started");
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

  //SAMPLE RAW DATA
  for (int i = 0; i < sample_n; i++) {
    real_x_axis[i] = analogRead(x_axis);
    real_y_axis[i] = analogRead(y_axis);
    real_z_axis[i] = analogRead(z_axis);
    // delayMicroseconds(1000 / sample_rate);
    delay(delay_rate);
  }

  //SAMPLE ACCEL DATA
  for (int i = 0; i < sample_n; i++) {
    xAccel[i] = (real_x_axis[i] * vRef / (adc_resolution - 1) - x_zero);
    yAccel[i] = (real_y_axis[i] * vRef / (adc_resolution - 1) - y_zero);
    zAccel[i] = (real_z_axis[i] * vRef / (adc_resolution - 1) - z_zero);
  }

  Serial.print(findMax(xAccel));
  Serial.print(" ");
  Serial.print(findMax(yAccel));
  Serial.print(" ");
  Serial.println(findMax(zAccel));

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

  // //PRINTING MAX FFTS VALS
  // Serial.print(findMax(xAccel));
  // Serial.print(" ");
  // Serial.print(findMax(yAccel));
  // Serial.print(" ");
  // Serial.println(findMax(zAccel));

  //SEND DATA PACKETS 
  double data1 = findMax(xAccel);
  double data2 = findMax(yAccel);
  double data3 = findMax(zAccel);
  // uint8_t bytes[sizeof(double) * 3]; //sending 3 x doubles which are max accel vals
  // uint8_t buffer[packetSize];
  // memcpy(buffer, &data1, sizeof(double));
  // memcpy(buffer + sizeof(double), &data2, sizeof(double));
  // memcpy(buffer + 2 * sizeof(double), &data3, sizeof(double));
  


  // uint8_t bytes[sizeof(real_x_axis)];
  // for (int i = 0; i < sizeof(real_x_axis); i += sizeof(double)) {
  //   double val = real_x_axis[i / sizeof(double)];
  //   memcpy(&bytes[i], &val, sizeof(double));
  // }

  LoRa.beginPacket();
  // LoRa.write(buffer, packetSize);
  LoRa.write((uint8_t*)&data1, sizeof(data1));
  LoRa.write((uint8_t*)&data2, sizeof(data2));  
  LoRa.write((uint8_t*)&data3, sizeof(data3));
  LoRa.endPacket();

  // delay(10000);
}



  // memcpy(bytes, &real_x_axis, sizeof(real_x_axis));

  // double* vReal = xFFT.getVReal();
  // for(int i = 0; i < sample_n; i++) {
  //   Serial.println(vReal[i]);
  // }




  // FFT.Compute()

  //Need to sample the data on each axis
  //Initialise structures to hold sampled data of length sample size
  // double sample_x_axis[sample_n];
  // double sample_y_axis[sample_n];
  // double sample_z_axis[sample_n];
  // //Initialise imaginary array to zeros
  // double vImag_x[sample_n] = {};
  // double vImag_y[sample_n] = {};
  // double vImag_z[sample_n] = {};
  // //Initialise average axis values
  // double average_x_axis = 0;
  // double average_y_axis = 0;
  // double average_z_axis = 0;
  //Sample each axis
  // for (int i = 0; i < sample_n; i++) {
  //   sample_x_axis[i] = readAxis(x_axis);
  //   sample_y_axis[i] = readAxis(y_axis);
  //   sample_z_axis[i] = readAxis(z_axis);
  //   //Period
  //   delay(1000 / sample_freq);
  // }
  //Need to create an object in scope for each axis
  //Previous intialisation is deprecated -> need to define with vreal and vimag now
  // arduinoFFT xFFT(sample_x_axis, vImag_x, sample_n, sample_freq);
  // arduinoFFT yFFT(sample_y_axis, vImag_y, sample_n, sample_freq);
  // arduinoFFT zFFT(sample_z_axis, vImag_z, sample_n, sample_freq);
  // //Non-empty method is now deprecated
  // xFFT.ComplexToMagnitude();
  // yFFT.ComplexToMagnitude();
  // zFFT.ComplexToMagnitude();
  // //Find the magnitude of FFT
  // for (int i = 0; i < (sample_n/2); i++) {
  //   double mag_x = 2 * sqrt(pow(sample_x_axis[i], 2) + pow(vImag_x[i], 2)) / sample_n;
  //   double mag_y = 2 * sqrt(pow(sample_y_axis[i], 2) + pow(vImag_y[i], 2)) / sample_n;
  //   double mag_z = 2 * sqrt(pow(sample_z_axis[i], 2) + pow(vImag_z[i], 2)) / sample_n;
  //   double freq = (i * sample_freq) / sample_n;
  //   // Serial.print("freq\t=\t");
  //   // Serial.println(freq);
  //   // Serial.print("mag\t=\t");
  //   // Serial.print(mag_x);
  //   // Serial.print("\t");
  //   // Serial.print(mag_y);
  //   // Serial.print("\t");
  //   // Serial.println(mag_z);
  //   average_x_axis += mag_x;
  //   average_y_axis += mag_y;
  //   average_z_axis += mag_z;
  // }
  // //Calculating the average magnitudes
  // average_x_axis /= (sample_n / 2);
  // average_y_axis /= (sample_n / 2);
  // average_z_axis /= (sample_n / 2);
  // //Packaging axis data and sending over LoRa
  // LoRa.beginPacket();
  // LoRa.print(average_x_axis);
  // LoRa.print(average_y_axis);
  // LoRa.print(average_z_axis);
  // LoRa.es
  // //10 second delay
  // delay(10000);
