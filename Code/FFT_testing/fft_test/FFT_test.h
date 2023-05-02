#ifndef FFT_TEST_H
#define FFT_TEST_H

#include <iostream>
#include <cmath>
#include <array>
#include "Arduino.h"
#include <arduinoFFT.h>
#include <math.h>

#define window_type FFT_WIN_TYP_HAMMING
#define FFT_dir FFT_FORWARD

constexpr double pi = 3.14159265358979323846;
constexpr int num_samples = 32;
constexpr double frequency = 2.0;
constexpr double sampling_rate = num_samples * frequency;

void genSineWave(double arr[]);

#endif