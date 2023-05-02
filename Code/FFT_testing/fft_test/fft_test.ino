#include "FFT_test.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Setup complete");
}

void loop() {
  double sineWave[num_samples] {};
  double imag_x_axis[num_samples] {};

  genSineWave(sineWave);

  arduinoFFT xFFT = arduinoFFT(sineWave, imag_x_axis, num_samples, sampling_rate);
  xFFT.Windowing(window_type, FFT_dir);
  xFFT.Compute(FFT_dir);
  xFFT.ComplexToMagnitude();
  double freqX = xFFT.MajorPeak();

  Serial.print("Frequency = ");
  Serial.print(freqX);
  Serial.println("Hz");
  delay(5000);
}