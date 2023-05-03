#include "Sender.h"

void genSineWave(double arr[]) {
    for (int i = 0; i < sample_n; ++i) {
        arr[i] = std::sin(2 * pi * frequency * i / sampling_rate);
    }
}

void genZeroWave(double arr[]) {
    for (int i = 0; i < sample_n; ++i) {
        arr[i] = 1;
    }
}

void printAxisValues(double xVal[], double yVal[], double zVal[]) {
    for (int i = 0; i < sample_n; i++) {
        Serial.print(xVal[i]);
        Serial.print(" ");
        Serial.print(yVal[i]);
        Serial.print(" ");
        Serial.println(zVal[i]);
    }
}

void printAxisVal(double xVal, double yVal, double zVal) {
    Serial.print(xVal);
    Serial.print(" ");
    Serial.print(yVal);
    Serial.print(" ");
    Serial.println(zVal);
}

void printAxisValueSingle(double accel[]) {
    for (int i = 0; i < sample_n; i++) {
        Serial.println(accel[i]);
    }
}

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