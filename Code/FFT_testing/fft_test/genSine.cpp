#include "FFT_test.h"

void genSineWave(double arr[]) {
    for (int i = 0; i < num_samples; ++i) {
        arr[i] = std::sin(2 * pi * frequency * i / sampling_rate);
    }
}