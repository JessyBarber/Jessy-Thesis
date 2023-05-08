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

// STATIC MEANS HAVE TO DELETE BUILD FILES IF I WANT TO REMOVE THE VARIABLE

static constexpr double pi = 3.14159265358979323846;

//---------- Accelerometer Values ----------
static const int x_axis = A1;
static const int y_axis = A2;
static const int z_axis = A3;
static const int adc_resolution = 4096; //12 BIT ADC
static const double g = 9.81;
const double noiseThreshold = 0.1;
// CALIBRATION
const double vRef = 3.3; //3.3V reference / supply
// const double vRef = 3.0; // BATTERY CONNECTION
static const double sensitivity = 0.33; //330 mV/g at 3.3V
//---------- Accelerometer Values ----------

//---------- FFT Values ----------
// static const int sample_rate = 4; //Want to capture 2Hz then need at least 4Hz but x 10 to get 20Hz
static const int frequency = 2;
// static const int maxFreq = 4;
static const int maxFreq = 10; // THIS IS THE MAXIMUM FREQUENCY THAT THE FFT CAN DETECT
static const uint16_t sample_n = 128; //MUST BE EXP 2
static const constexpr double sampling_rate = maxFreq * 2; // SAMPLING RATE MUST BE AT LEAST TWICE THE MAX FREQUENCY
// static constexpr double sampling_rate = frequency * sample_n;
static constexpr double sample_interval = ((1.0/sampling_rate) * 1000); //Gives sample interval in milliseconds
static constexpr uint16_t window_size = (1.0/maxFreq) * sampling_rate;
//To sample for 10 seconds -> N = 10/T = 10/(1/20) = 200 samples

//FFT Function Values
// #define window_type FFT_WIN_TYP_HAMMING
#define window_type FFT_WIN_TYP_HANN
#define FFT_dir FFT_FORWARD
//---------- FFT Values ----------

//---------- LoRa ----------
//Transmission Values 
// const int packetSize = 3 * sizeof(double); //Sending three doubles 
//---------- LoRa ----------

// ---------- FUNCTIONS ----------
// double findMax(double arr[]);s
double findMaxAbs(const double data[]);
// void lowPassFilter(double *input, double *output, int windowSize);
// void lowPassFilter(double arr[]);
void lowPassFilter(double *data, double alpha);
void addGravity(double arr[]);
int findMaxIndex(double arr[]);
double findAvg(double arr[]);
void removeBias(double arr[]);
void integrate(const double arr[], double dt, double integrated[]);
void readRawData(double real_x_axis[], double real_y_axis[], double real_z_axis[]);
void processRawData(double xAccel[], double yAccel[], double zAccel[], 
                    const double real_x_axis[], const double real_y_axis[], 
                    const double real_z_axis[], double xZero, double yZero, double zZero);
void integrate(const double xIn[], const double yIn[], const double zIn[], 
                double xOut[], double yOut[], double zOut[]);
// ---------- FUNCTIONS ----------

// ---------- TEST FUNCTIONS ----------
void genSineWave(double arr[]);
void genZeroWave(double arr[]);
void printAxisValues(double xAccel[], double yAccel[], double zAccel[]);
void printAxisVal(double xFreq, double yFreq, double zFreq);
void printAxisValueSingle(double accel[]);
void callibrate(int callibration_samples, double& xZero, double& yZero, double& zZero);
void checkNan(double& freq);
// ---------- TEST FUNCTIONS ----------

#endif