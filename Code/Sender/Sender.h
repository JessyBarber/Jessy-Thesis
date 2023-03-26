#ifndef Sender_h
#define Sender_h

#include "Arduino.h"
#include <MKRWAN.h>
#include <arduinoFFT.h>
#include <LoRa.h>
#include <stdio.h>


//Accelerometer Values
const int x_axis = A1;
const int y_axis = A2;
const int z_axis = A3;
const char x = 'x';
const char y = 'y';
const char z = 'z';

//FFT Values
//Sampling rate should be twice the highest freq in the signal
const uint16_t sample_n = 256;
const int sample_freq = 200;
//Definine window type and direction for FFT
#define window_type FFT_WIN_TYP_HAMMING
#define FFT_dir FFT_FORWARD

//Sensor.cpp
int readAxis(int axis);
void printAxis(char label, int axis);

//FFT.cpp
void setWindowing();

#endif