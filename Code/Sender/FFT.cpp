#include "Sender.h"
arduinoFFT FFT;
//Set the FFT windowing type
void setWindowing(){
  // FFT.Windowing(sample_n, window_type);
  FFT.Windowing(window_type, FFT_dir);
}