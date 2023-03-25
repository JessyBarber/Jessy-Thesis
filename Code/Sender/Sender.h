#ifndef Sender_h
#define Sender_h

#include "Arduino.h"
#include <MKRWAN.h>
#include <arduinoFFT.h>

// const int x_axis = A1;
const int y_axis = A2;
const int z_axis = A3;

int readAxis(int axis);
void printAxis(int axis);


#endif

