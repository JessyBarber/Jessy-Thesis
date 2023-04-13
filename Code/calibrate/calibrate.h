#ifndef CALlIBRATION_H
#define CALlIBRATION_H

#include "Arduino.h"

const int x_axis = A1;
const int y_axis = A2;
const int z_axis = A3;

const int adc_resolution = 4096.0;
const int samples = 1000;
// const double vRef = 3.0; //Battery source approximation
// const double sensitivity = 0.298125; // 298.125 mV/g at 3V
const double vRef = 3.3;
const double sensitivity = 0.33; // 330 mV/g at 3.3V (proportional to supply voltage)


#endif