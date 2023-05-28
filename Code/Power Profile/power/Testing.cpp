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