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
#include <new>

//FFT Function Values
#define window_type FFT_WIN_TYP_HAMMING
#define FFT_dir FFT_FORWARD
#define xPin A1
#define yPin A2
#define zPin A3

// //---------- Accelerometer Values ----------

static const int adc_resolution = 4096; //12 BITS

static const int sample_rate = 20; //Want to capture 2Hz then need at least 4Hz but x 10 to get 20Hz
static constexpr double sample_interval = ((1.0/sample_rate) * 1000);
static const uint16_t sample_n = 256; //MUST BE EXP 2
static constexpr double dt = sample_interval / 1000;
// 3.3 V 
static const double vRef = 3.3; //12 BITS
static const double sensitivity = 0.33; //330 mV/g at 3.3V
static const double x_zero = 0.386719;
static const double y_zero = 0.386719;
static const double z_zero = 0.134546;
// // 3.0 V 
// static const double vRef = 3.0;
// static const double sensitivity = 0.298125;
// static const double x_zero = 0.151611;
// static const double y_zero = 0.149414;
// static const double z_zero = -0.120850;

// //---------- Accelerometer Values ----------

class axis {
  private:
  public:
    double real_axis[sample_n] {};
    double imag_axis[sample_n] {};
    double Accel[sample_n] {};
    double AccelMSS[sample_n] {};
    double Vel[sample_n] {};
    double xDisp[sample_n] {};
    double voltage {};
    int maxIndex {};
    double frequency {};
    
    double findMax(double arr[]);
    void setMaxIndex();
    int findMaxIndex(double arr[]);
    void setFreq();
};

double axis::findMax(double *arr) {
  return *std::max_element(arr, arr+sample_n);
}

void axis::setMaxIndex() {
  this->maxIndex = findMaxIndex(this->Accel);
}

int axis::findMaxIndex(double *arr) {
  int maxIndex = 1;
  for (int i = 1; i < sample_n / 2; i++) { // Only need to search the first half of the array
    if (arr[i] > arr[maxIndex]) {
      maxIndex = i;
    }
  }
  return maxIndex;
}

void axis::setFreq() {
  this->frequency = this->maxIndex * ((double)sample_rate / (double)sample_n);
}

// int findMaxIndex(double arr[]) {
//   int maxIndex = 1;
//   for (int i = 1; i < sample_n / 2; i++) { // Only need to search the first half of the array
//     if (arr[i] > arr[maxIndex]) {
//       maxIndex = i;
//     }
//   }
//   return maxIndex;
// }
  

const double g = 9.81;


//---------- Accelerometer Values ----------

//---------- FFT Values ----------
// const int sample_rate = 20; //Want to capture 2Hz then need at least 4Hz but x 10 to get 20Hz
// const uint16_t sample_n = 256; //MUST BE EXP 2
// const double sample_interval = ((1.0/sample_rate) * 1000); //Gives sample interval in milliseconds
//To sample for 10 seconds -> N = 10/T = 10/(1/20) = 200 sampleszx

//---------- FFT Values ----------

//---------- LoRa ----------
//Transmission Values 
const int packetSize = 3 * sizeof(double); //Sending three doubles 
//---------- LoRa ----------

//---------- Functions ----------
// //Sensor.cpp
// int readAxis(int axis);
// void printAxis(char label, int axis);

//FFT.cpp
// double findMax(double arr[]);
// // void lowPassFilter(double *input, double *output, int windowSize);
// void addGravity(const double arr[], double gravitized[]);
// int findMaxIndex(double arr[]);
// double findAvg(double arr[]);
// void removeBias(double arr[], double bias);
// void integrate(const double arr[], double dt, double integrated[]);
//---------- Functions ----------

#endif