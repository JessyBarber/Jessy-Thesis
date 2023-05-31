#include "Sender.h"

void callibrate (int callibration_samples, double& xZero, double& yZero, double& zZero) {
    Serial.println("Calibrating Accelerometer...");

    double offsetX = 0;
    double offsetY = 0;
    double offsetZ = 0;

    for (int i = 0; i < callibration_samples; i++) {
        double rawX = analogRead(x_axis);
        double rawY = analogRead(y_axis);
        double rawZ = analogRead(z_axis);

        double voltageX = (rawX * vRef) / (adc_resolution - 1);
        double voltageY = (rawY * vRef) / (adc_resolution - 1);
        double voltageZ = (rawZ * vRef) / (adc_resolution - 1);

        double accelerationX = (voltageX - vRef / 2) / sensitivity;
        double accelerationY = (voltageY - vRef / 2) / sensitivity;
        double accelerationZ = (voltageZ - vRef / 2) / sensitivity - 1;

        offsetX += accelerationX;
        offsetY += accelerationY;
        offsetZ += accelerationZ;
        delay(10);
    }

    offsetX /= callibration_samples;
    offsetY /= callibration_samples;
    offsetZ /= callibration_samples;

    // ---------- MUST BE TURNED OFF IF PWR IS BATTERY ----------
    // Serial.print("Offset X: ");
    // Serial.println(offsetX, 6);
    // Serial.print("Offset Y: ");
    // Serial.println(offsetY, 6);
    // Serial.print("Offset ccoffsetZ: ");
    // Serial.println(offsetZ, 6);
    // ---------- MUST BE TURNED OFF IF PWR IS BATTERY ----------

    xZero = offsetX;
    yZero = offsetY;
    zZero = offsetZ;
}

double findMaxAbs(const double data[]) {
  double maxVal = 0;
  for (int i = 0; i < sample_n; ++i) {
    double absVal = abs(data[i]);
    if (absVal > maxVal) {
      maxVal = absVal;
    }
  }
  return maxVal;
}

double findMax(const double data[]) {
  double maxVal = 0;
  for (int i = 0; i < sample_n; ++i) {
    double absVal = data[i];
    if (absVal > maxVal) {
      maxVal = absVal;
    }
  }
  return maxVal;
}

void lowPassFilter(double *data) {
  double filteredData = data[0]; // Initialize with the first value of the data array

  for (uint16_t i = 1; i < sample_n; i++) {
    filteredData = LP_alpha * data[i] + (1.0 - LP_alpha) * filteredData;
    data[i] = filteredData;
  }
}

double findAvg(double arr[]) {
  double sum = 0.0;
  for (int i = 0; i < sample_n; i++) {
    sum += arr[i];
  }
  return sum / sample_n;
}

void removeBias(double arr[]) { 
  double bias = findAvg(arr);
  for (int i = 0; i < sample_n; i++) {
    arr[i] -= bias;
  }
}

void readRawData(double real_x_axis[], double real_y_axis[], double real_z_axis[]) {
  for (int i = 0; i < sample_n; i++) {
    // READ RAW DATA FROM ANALOG PINS
    real_x_axis[i] = analogRead(x_axis);
    real_y_axis[i] = analogRead(y_axis);
    real_z_axis[i] = analogRead(z_axis);
    // SAMPLING INTERVAL
    delay(sample_interval);
  }
}

void processRawData(double xAccel[], double yAccel[], double zAccel[], 
                    const double real_x_axis[], const double real_y_axis[], 
                    const double real_z_axis[], double xZero, double yZero, double zZero) {
  for (int i = 0; i < sample_n; i++) {
    // CONVERT ADC LEVEL TO A VOLTAGE
    double voltageX = ((real_x_axis[i] * vRef) / (adc_resolution - 1));
    double voltageY = ((real_y_axis[i] * vRef) / (adc_resolution - 1));
    double voltageZ = ((real_z_axis[i] * vRef) / (adc_resolution - 1));

    xAccel[i] = ((voltageX - vRef / 2) / sensitivity - xZero) * g;
    yAccel[i] = ((voltageY - vRef / 2) / sensitivity - yZero) * g;
    zAccel[i] = ((voltageZ - vRef / 2) / sensitivity - zZero - 1) * g; // Subtract gravity

    // // Apply threshold to remove noise
    xAccel[i] = (abs(xAccel[i]) <= 0.7) ? 0 : xAccel[i];
    yAccel[i] = (abs(yAccel[i]) <= 0.9) ? 0 : yAccel[i];
    zAccel[i] = (abs(zAccel[i]) <= 0.1) ? 0 : zAccel[i];
  }
}

void checkNan(float& freq) {
 if (isnan(freq)) {
  freq = 0;
 }
}