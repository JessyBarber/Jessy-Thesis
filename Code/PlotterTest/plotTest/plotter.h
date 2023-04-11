#ifndef PLOTTER_H
#define PLOTTER_H

#include "Arduino.h"
#include <MKRWAN.h>
#include <arduinoFFT.h>
#include <LoRa.h>
#include <stdio.h>
#include <algorithm> 

//Accelerometer Values
const int x_axis = A1;
const int y_axis = A2;
const int z_axis = A3;
const int adc_resolution = 4096; //12 BITS
const double vRef = 3.3; //3.3V reference / supply
const double sensitivity = 0.33; //330 mV/g at 3.3V
const double x_zero = 0.42;
const double y_zero = 0.41;
const double z_zero = 0.50;

//FFT Values
const uint16_t sample_n = 128; //MUST BE EXP 2
const int sample_rate = 200;
//Definine window type and direction for FFT
#define window_type FFT_WIN_TYP_HAMMING
#define FFT_dir FFT_FORWARD

//Sensor.cpp
int readAxis(int axis);
void printAxis(char label, int axis);

//plotHandle
void deMean(double *axis_data);
double findMax(double arr[]);

#endif