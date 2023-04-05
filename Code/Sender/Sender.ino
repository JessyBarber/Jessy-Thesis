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
  //Set the FFT windowing type and direction
  //Definitions in header file
  // setWindowing();

  // FFT.Windowing(window_type, FFT_dir);
}

void loop() {
  double real_x_axis[sample_n] {};
  // double sample_x_axis[sample_n] {};
  double imag_x_axis[sample_n] {};

  for (int i = 0; i < sample_n; i++){
    // sample_x_axis[i] = analogRead(x_axis);
    real_x_axis[i] = analogRead(x_axis);
    delayMicroseconds(1000/sample_rate);
  }

  arduinoFFT xFFT(real_x_axis, imag_x_axis, sample_n, sample_rate);
  Serial.println("Creating window");
  xFFT.Windowing(window_type, FFT_dir);
  Serial.println("Computing");
  xFFT.Compute(FFT_dir);
  Serial.println("Converting to Magnitude");
  xFFT.ComplexToMagnitude();

  for (int i = 0; i < sample_n; i++){
    Serial.println(real_x_axis[i]);
  }

  uint8_t bytes[sizeof(real_x_axis)];
  for (int i = 0; i < sizeof(real_x_axis); i += sizeof(double)) {
    double val = real_x_axis[i / sizeof(double)];
    memcpy(&bytes[i], &val, sizeof(double));
  }

  // memcpy(bytes, &real_x_axis, sizeof(real_x_axis));
  LoRa.beginPacket();
  LoRa.write(bytes, sizeof(real_x_axis));
  LoRa.endPacket();

  // double* vReal = xFFT.getVReal();
  // for(int i = 0; i < sample_n; i++) {
  //   Serial.println(vReal[i]);
  // }



  delay(10000);


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
  // LoRa.endPacket();
  // //10 second delay
  // delay(10000);
}