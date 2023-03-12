#include <Wire.h>
#include <arduinoFFT.h>
#include <MKRWAN.h>
#include <LoRa.h>

#define SAMPLES 256 // number of samples to use for FFT
#define SAMPLING_FREQ 200 // sampling frequency in Hz
#define ACCELEROMETER_PIN_X A0
#define ACCELEROMETER_PIN_Y A1
#define ACCELEROMETER_PIN_Z A2

LoRaModem modem; // create LoRa modem object
arduinoFFT FFT; // create FFT object
double vRealX[SAMPLES];
double vImagX[SAMPLES];
double vRealY[SAMPLES];
double vImagY[SAMPLES];
double vRealZ[SAMPLES];
double vImagZ[SAMPLES];

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa Modem Started");
  FFT.Windowing(FFT_WIN_TYP_HAMMING, SAMPLES); // set FFT window type
}

void loop() {
  int16_t accelerometerDataX[SAMPLES]; // array to hold accelerometer X-axis data
  int16_t accelerometerDataY[SAMPLES]; // array to hold accelerometer Y-axis data
  int16_t accelerometerDataZ[SAMPLES]; // array to hold accelerometer Z-axis data
  for (int i = 0; i < SAMPLES; i++) {
    accelerometerDataX[i] = analogRead(ACCELEROMETER_PIN_X);
    accelerometerDataY[i] = analogRead(ACCELEROMETER_PIN_Y);
    accelerometerDataZ[i] = analogRead(ACCELEROMETER_PIN_Z);
    delay(1000/SAMPLING_FREQ); // wait for sampling interval
  }
  for (int i = 0; i < SAMPLES; i++) {
    vRealX[i] = accelerometerDataX[i]; // copy X-axis data to real component
    vImagX[i] = 0; // set imaginary component to zero
    vRealY[i] = accelerometerDataY[i]; // copy Y-axis data to real component
    vImagY[i] = 0; // set imaginary component to zero
    vRealZ[i] = accelerometerDataZ[i]; // copy Z-axis data to real component
    vImagZ[i] = 0; // set imaginary component to zero
  }
  FFT.ComplexToMagnitude(vRealX, vImagX, SAMPLES); // perform FFT on X-axis data
  FFT.ComplexToMagnitude(vRealY, vImagY, SAMPLES); // perform FFT on Y-axis data
  FFT.ComplexToMagnitude(vRealZ, vImagZ, SAMPLES); // perform FFT on Z-axis data
  double averageFrequencyX = 0.0;
  double averageFrequencyY = 0.0;
  double averageFrequencyZ = 0.0;
  for (int i = 0; i < (SAMPLES/2); i++) {
    double magnitudeX = 2 * sqrt(pow(vRealX[i], 2) + pow(vImagX[i], 2)) / SAMPLES;
    double frequencyX = (i * SAMPLING_FREQ) / SAMPLES;
    Serial.print(frequencyX); // print frequency value
    Serial.print("\t");
    Serial.println(magnitudeX); // print magnitude value
    averageFrequencyX +=magnitudeX;}
  for (int i = 0; i < (SAMPLES/2); i++) {
    double magnitudeY = 2 * sqrt(pow(vRealY[i], 2) + pow(vImagY[i], 2)) / SAMPLES;
    double frequencyY = (i * SAMPLING_FREQ) / SAMPLES;
    Serial.print(frequencyY); // print frequency value
    Serial.print("\t");
    Serial.println(magnitudeY); // print magnitude value
    averageFrequencyY +=magnitudeY;}
  for (int i = 0; i < (SAMPLES/2); i++) {
    double magnitudeZ = 2 * sqrt(pow(vRealZ[i], 2) + pow(vImagZ[i], 2)) / SAMPLES;
    double frequencyZ = (i * SAMPLING_FREQ) / SAMPLES;
    Serial.print(frequencyZ); // print frequency value
    Serial.print("\t");
    Serial.println(magnitudeZ); // print magnitude value
    averageFrequencyZ +=magnitudeZ;
      }
  
  averageFrequencyX /= (SAMPLES/2);
  averageFrequencyY /= (SAMPLES/2);
  averageFrequencyZ /= (SAMPLES/2);
   Serial.print("Average Frequency X: ");
  Serial.println(averageFrequencyX);
    Serial.print("Average Frequency Y: ");
  Serial.println(averageFrequencyY);
    Serial.print("Average Frequency Z: ");
  Serial.println(averageFrequencyZ);
  LoRa. beginPacket();
  LoRa.print(averageFrequencyX);
  LoRa.print(averageFrequencyY);
  LoRa.print(averageFrequencyZ);
  LoRa.endPacket();
  delay(10000); // wait for 10 seconds
}
