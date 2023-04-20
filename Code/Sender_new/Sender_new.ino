#include "Sender.h"

// Create and initialize arduinoFFT objects
alignas(arduinoFFT) uint8_t xFFTBuffer[sizeof(arduinoFFT)];
alignas(arduinoFFT) uint8_t yFFTBuffer[sizeof(arduinoFFT)];
alignas(arduinoFFT) uint8_t zFFTBuffer[sizeof(arduinoFFT)];

arduinoFFT &xFFT = rienterpret_cast<arduinoFFT&>(xFFTBuffer);
arduinoFFT &yFFT = reinterpret_cast<arduinoFFT&>(yFFTBuffer);
arduinoFFT &zFFT = reinterpret_cast<arduinoFFT&>(zFFTBuffer);

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
  Serial.println("LoRa Modem Started");
  //Initialise LoRa connection
  LoRa.begin(915E6);
  // LoRa.setFrequency(915E6);
}

void loop() {

  axis x_axis, y_axis, z_axis;


  for (int i = 0; i < sample_n; i++) {
    x_axis.real_axis[i] = analogRead(xPin);
    y_axis.real_axis[i] = analogRead(yPin);
    z_axis.real_axis[i] = analogRead(zPin);
    delay(sample_interval);
  }

  //SAMPLE ACCEL DATA
  for (int i = 0; i < sample_n; i++) {
    x_axis.voltage = x_axis.real_axis[i] * vRef / (adc_resolution - 1);
    y_axis.voltage = y_axis.real_axis[i] * vRef / (adc_resolution - 1);
    z_axis.voltage = z_axis.real_axis[i] * vRef / (adc_resolution - 1);

    x_axis.Accel[i] = (x_axis.voltage - x_zero) / sensitivity;
    y_axis.Accel[i] = (y_axis.voltage - y_zero) / sensitivity;
    z_axis.Accel[i] = ((z_axis.voltage - z_zero) / sensitivity) - 1.0; // subtract Earth's gravity
  }

  //COMPUTE FFT
  new (&xFFT) arduinoFFT(x_axis.Accel, x_axis.imag_axis, sample_n, sample_rate);
  new (&yFFT) arduinoFFT(y_axis.Accel, y_axis.imag_axis, sample_n, sample_rate);
  new (&zFFT) arduinoFFT(z_axis.Accel, z_axis.imag_axis, sample_n, sample_rate);
  // xFFT(x_axis.Accel, x_axis.imag_axis, sample_n, sample_rate);
  // arduinoFFT yFFT(y_axis.Accel, y_axis.imag_axis, sample_n, sample_rate);
  // arduinoFFT zFFT(z_axis.Accel, z_axis.imag_axis, sample_n, sample_rate);

  // xFFT.Windowing(window_type, FFT_dir);
  // yFFT.Windowing(window_type, FFT_dir);
  // zFFT.Windowing(window_type, FFT_dir);

  // xFFT.Compute(FFT_dir);
  // yFFT.Compute(FFT_dir);
  // zFFT.Compute(FFT_dir);

  // xFFT.ComplexToMagnitude();
  // yFFT.ComplexToMagnitude();
  // zFFT.ComplexToMagnitude();

  // x_axis.setMaxIndex();
  // y_axis.setMaxIndex();
  // z_axis.setMaxIndex();

  // x_axis.setFreq();
  // y_axis.setFreq();
  // z_axis.setFreq();

  // // Send Frequency, Acceleration & Displacement
  // // TRANSMIT LORA PACKET
  // LoRa.beginPacket();
  // // LoRa.write(buffer, packetSize);
  // LoRa.write((uint8_t*)&x_axis.frequency, sizeof(x_axis.frequency));
  // LoRa.write((uint8_t*)&y_axis.frequency, sizeof(y_axis.frequency));  
  // LoRa.write((uint8_t*)&z_axis.frequency, sizeof(z_axis.frequency));
  // LoRa.endPacket();






  // LoRa.write((uint8_t*)&maxAccelX, sizeof(maxAccelX));
  // LoRa.write((uint8_t*)&maxAccelY, sizeof(maxAccelY));
  // LoRa.write((uint8_t*)&maxAccelZ, sizeof(maxAccelZ));

  // LoRa.write((uint8_t*)&maxDispX, sizeof(maxDispX));
  // LoRa.write((uint8_t*)&maxDispY, sizeof(maxDispY));
  // LoRa.write((uint8_t*)&maxDispZ, sizeof(maxDispZ));



  



  // //ACCELERATION SAMPLING
  // double xAccel[sample_n] {};
  // double yAccel[sample_n] {};
  // double zAccel[sample_n] {};
  // double xAccelMSS[sample_n] {};
  // double yAccelMSS[sample_n] {};
  // double zAccelMSS[sample_n] {};

  // //VELOCITY SAPLING
  // double xVel[sample_n] {};
  // double yVel[sample_n] {};
  // double zVel[sample_n] {};

  // //DISPLACEMENT SAMPLING
  // double xDisp[sample_n] {};
  // double yDisp[sample_n] {};
  // double zDisp[sample_n] {};

  // //Sample interval in seconds for integration
  // double dt = sample_interval / 1000;

  // // long int t1 = millis();
  // //SAMPLE RAW DATA
  // for (int i = 0; i < sample_n; i++) {
  //   real_x_axis[i] = analogRead(x_axis);
  //   real_y_axis[i] = analogRead(y_axis);
  //   real_z_axis[i] = analogRead(z_axis);
  //   delay(sample_interval);
  // }
  // // long int t2 = millis();
  // // Serial.print("Time taken: "); Serial.print((t2-t1)/1000); Serial.println(" s");

  // //-------------------- DEBUGGING --------------------
  // //-------------------- DEBUGGING --------------------

  // //SAMPLE ACCEL DATA
  // for (int i = 0; i < sample_n; i++) {
  //   // xAccel[i] = (real_x_axis[i] * vRef / (adc_resolution - 1) - x_zero);
  //   // yAccel[i] = (real_y_axis[i] * vRef / (adc_resolution - 1) - y_zero);
  //   // zAccel[i] = (real_z_axis[i] * vRef / (adc_resolution - 1) - z_zero);

  //   double voltageX = real_x_axis[i] * vRef / (adc_resolution - 1);
  //   double voltageY = real_y_axis[i] * vRef / (adc_resolution - 1);
  //   double voltageZ = real_z_axis[i] * vRef / (adc_resolution - 1);

  //   xAccel[i] = (voltageX - x_zero) / sensitivity;
  //   yAccel[i] = (voltageY - y_zero) / sensitivity;
  //   zAccel[i] = ((voltageZ - z_zero) / sensitivity) - 1.0; // subtract Earth's gravity
  // }

  // //CONVERT ACCELERATION FROM G'S TO M/S/S
  // addGravity(xAccel, xAccelMSS);
  // addGravity(yAccel, yAccelMSS);
  // addGravity(zAccel, zAccelMSS);

  // // //REMOVE BIAS
  // // double accel_x_bias = findAvg(xAccel);
  // // double accel_y_bias = findAvg(yAccel);
  // // double accel_z_bias = findAvg(zAccel);

  // // removeBias(xAccel, accel_x_bias);
  // // removeBias(yAccel, accel_y_bias);
  // // removeBias(zAccel, accel_z_bias);
  // // Serial.println("Removed Bias");
  // //FIND VELOCITY
  // // integrate(xAccelMSS, dt, xVel);
  // // integrate(yAccelMSS, dt, yVel);
  // // integrate(zAccelMSS, dt, zVel);
  // // Serial.print("Integrated");
  // // //REMOVE DRIFT 
  // // double vel_x_drift = findAvg(xVel);
  // // double vel_y_drift = findAvg(yVel);
  // // double vel_z_drift = findAvg(zVel);

  // // removeBias(xVel, vel_x_drift);
  // // removeBias(yVel, vel_y_drift);
  // // removeBias(zVel, vel_z_drift);

  // // //FIND DISPLACEMENT
  // // integrate(xVel, dt, xDisp);
  // // integrate(yVel, dt, yDisp);
  // // integrate(zVel, dt, zDisp);

  // // //FIND MAX ACCELERATION VALS
  // // double maxAccelX = findMax(xAccelMSS);
  // // double maxAccelY = findMax(yAccelMSS);
  // // double maxAccelZ = findMax(zAccelMSS);

  // // //FIND MAX DISPLACEMENT VALS
  // // double maxDispX = findMax(xDisp);
  // // double maxDispY = findMax(yDisp);
  // // double maxDispZ = findMax(zDisp);

  // //COMPUTE FFT
  // arduinoFFT xFFT(xAccel, imag_x_axis, sample_n, sample_rate);
  // arduinoFFT yFFT(yAccel, imag_y_axis, sample_n, sample_rate);
  // arduinoFFT zFFT(zAccel, imag_z_axis, sample_n, sample_rate);

  // xFFT.Windowing(window_type, FFT_dir);
  // yFFT.Windowing(window_type, FFT_dir);
  // zFFT.Windowing(window_type, FFT_dir);

  // xFFT.Compute(FFT_dir);
  // yFFT.Compute(FFT_dir);
  // zFFT.Compute(FFT_dir);

  // xFFT.ComplexToMagnitude();
  // yFFT.ComplexToMagnitude();
  // zFFT.ComplexToMagnitude();

  // int maxIndexX = findMaxIndex(xAccel);
  // int maxIndexY = findMaxIndex(yAccel);
  // int maxIndexZ = findMaxIndex(zAccel);

  // double frequencyX = maxIndexX * ((double)sample_rate / (double)sample_n);
  // double frequencyY = maxIndexY * ((double)sample_rate / (double)sample_n);
  // double frequencyZ = maxIndexZ * ((double)sample_rate / (double)sample_n);

  // // Send Frequency, Acceleration & Displacement
  // // TRANSMIT LORA PACKET
  // LoRa.beginPacket();
  // // LoRa.write(buffer, packetSize);
  // LoRa.write((uint8_t*)&frequencyX, sizeof(frequencyX));
  // LoRa.write((uint8_t*)&frequencyY, sizeof(frequencyY));  
  // LoRa.write((uint8_t*)&frequencyZ, sizeof(frequencyZ));

  // // LoRa.write((uint8_t*)&maxAccelX, sizeof(maxAccelX));
  // // LoRa.write((uint8_t*)&maxAccelY, sizeof(maxAccelY));
  // // LoRa.write((uint8_t*)&maxAccelZ, sizeof(maxAccelZ));

  // // LoRa.write((uint8_t*)&maxDispX, sizeof(maxDispX));
  // // LoRa.write((uint8_t*)&maxDispY, sizeof(maxDispY));
  // // LoRa.write((uint8_t*)&maxDispZ, sizeof(maxDispZ));
  // LoRa.endPacket();
  // // delay(10000);
}