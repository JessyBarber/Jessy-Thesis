#include "Sender.h"

// extern "C" char* sbrk(int incr);
// int freeSRAM() {
//   char top;
//   return &top - reinterpret_cast<char*>(sbrk(0));
// }

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

  //ACCELERATION SAMPLING
  double xAccel[sample_n] {};
  double yAccel[sample_n] {};
  double zAccel[sample_n] {};

  //VELOCITY SAPLING
  double xVel[sample_n] {};
  double yVel[sample_n] {};
  double zVel[sample_n] {};

  //DISPLACEMENT SAMPLING
  double xDisp[sample_n] {};
  double yDisp[sample_n] {};
  double zDisp[sample_n] {};

  //Sample interval in seconds for integration
  double dt = sample_interval / 1000;

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

  for(int i = 0; i < sample_n; i++) {
    Serial.print(xAccel[i]);
    Serial.print(" ");
    Serial.print(yAccel[i]);
    Serial.print(" ");
    Serial.println(zAccel[i]);
  }
  //CONVERT ACCELERATION FROM G'S TO M/S/S
  addGravity(xAccel);
  addGravity(yAccel);
  addGravity(zAccel);

  // //REMOVE BIAS
  // double accel_x_bias = findAvg(xAccel);
  // double accel_y_bias = findAvg(yAccel);
  // double accel_z_bias = findAvg(zAccel);

  // removeBias(xAccel, accel_x_bias);
  // removeBias(yAccel, accel_y_bias);
  // removeBias(zAccel, accel_z_bias);

  // //FIND VELOCITY
  // integrate(xAccel, dt, xVel);
  // integrate(yAccel, dt, yVel);
  // integrate(zAccel, dt, zVel);

  // //REMOVE DRIFT 
  // double vel_x_drift = findAvg(xVel);
  // double vel_y_drift = findAvg(yVel);
  // double vel_z_drift = findAvg(zVel);

  // removeBias(xVel, vel_x_drift);
  // removeBias(yVel, vel_y_drift);
  // removeBias(zVel, vel_z_drift);

  // //FIND DISPLACEMENT
  // integrate(xVel, dt, xDisp);
  // integrate(yVel, dt, yDisp);
  // integrate(zVel, dt, zDisp);

  //FIND MAX ACCELERATION VALS
  double maxAccelX = findMax(xAccel);
  double maxAccelY = findMax(yAccel);
  double maxAccelZ = findMax(zAccel);

  // //FIND MAX DISPLACEMENT VALS
  // double maxDispX = findMax(xDisp);
  // double maxDispY = findMax(yDisp);
  // double maxDispZ = findMax(zDisp);

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

  int maxIndexX = findMaxIndex(xAccel);
  int maxIndexY = findMaxIndex(yAccel);
  int maxIndexZ = findMaxIndex(zAccel);

  double frequencyX = maxIndexX * ((double)sample_rate / (double)sample_n);
  double frequencyY = maxIndexY * ((double)sample_rate / (double)sample_n);
  double frequencyZ = maxIndexZ * ((double)sample_rate / (double)sample_n);

  // int available_sram = freeSRAM();
  // Serial.print("Available SRAM: ");
  // Serial.println(available_sram);

  //Send Frequency, Acceleration & Displacement
  // TRANSMIT LORA PACKET
  LoRa.beginPacket();
  LoRa.write((uint8_t*)&frequencyX, sizeof(frequencyX));
  LoRa.write((uint8_t*)&frequencyY, sizeof(frequencyY));  
  LoRa.write((uint8_t*)&frequencyZ, sizeof(frequencyZ));

  LoRa.write((uint8_t*)&maxAccelX, sizeof(maxAccelX));
  LoRa.write((uint8_t*)&maxAccelY, sizeof(maxAccelY));
  LoRa.write((uint8_t*)&maxAccelZ, sizeof(maxAccelZ));

  // LoRa.write((uint8_t*)&maxDispX, sizeof(maxDispX));
  // LoRa.write((uint8_t*)&maxDispY, sizeof(maxDispY));
  // LoRa.write((uint8_t*)&maxDispZ, sizeof(maxDispZ));
  LoRa.endPacket();
  // delay(10000);
}