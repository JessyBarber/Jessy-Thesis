#ifndef CALlIBRATION_H
#define CALlIBRATION_H

#include "Arduino.h"

const int x_axis = A1;
const int y_axis = A2;
const int z_axis = A3;

// const uint16_t sample_n = 2;
// const int sample_rate = 20;
const int calibration_n = 4096;
const double vRef = 3.3;
const double sensitivity = 0.33; // 330mV/g at 3.3V (proportional to supply voltage)

#endif