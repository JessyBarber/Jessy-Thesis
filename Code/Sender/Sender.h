#ifndef Sender_h
#define Sender_h

#include "Arduino.h"
#include <algorithm>
#include <math.h>
#include <MKRWAN.h>
#include <arduinoFFT.h>
#include <LoRa.h>
#include <stdio.h>
#include <iostream> 

//---------- Accelerometer Values ----------
const int x_axis = A1;
const int y_axis = A2;
const int z_axis = A3;
const int adc_resolution = 4096; //12 BITS
const double vRef = 3.3; //3.3V reference / supply
const double sensitivity = 0.33; //330 mV/g at 3.3V

//Callibration Values
const double x_zero = 0.42;
const double y_zero = 0.41;
const double z_zero = 0.50;
//---------- Accelerometer Values ----------

//---------- FFT Values ----------
const int sample_rate = 20; //Want to capture 2Hz then need at least 4Hz but x 10 to get 20Hz
const uint16_t sample_n = 128; //MUST BE EXP 2
const double sample_interval = ((1.0/sample_rate) * 1000); //Gives sample interval in milliseconds
//To sample for 10 seconds -> N = 10/T = 10/(1/20) = 200 sampleszx

//FFT Function Values
#define window_type FFT_WIN_TYP_HAMMING
#define FFT_dir FFT_FORWARD
//---------- FFT Values ----------

//---------- LoRa ----------
//Transmission Values 
const int packetSize = 3 * sizeof(double); //Sending three doubles 
//---------- LoRa ----------

//---------- Functions ----------
//Sensor.cpp
int readAxis(int axis);
void printAxis(char label, int axis);

//FFT.cpp
void deMean(double *axis_data);
double findMax(double arr[]);
//---------- Functions ----------

#endif