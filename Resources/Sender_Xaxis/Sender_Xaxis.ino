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
double vReal[SAMPLES];
double vImag[SAMPLES];

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
    vReal[i] = accelerometerDataX[i]; // copy X-axis data to real component
    vImag[i] = 0; // set imaginary component to zero
  }
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES); // perform FFT on X-axis data
  double averageFrequency = 0.0;
  for (int i = 0; i < (SAMPLES/2); i++) {
    double magnitude = 2 * sqrt(pow(vReal[i], 2) + pow(vImag[i], 2)) / SAMPLES;
    double frequency = (i * SAMPLING_FREQ) / SAMPLES;
    Serial.print(frequency); // print frequency value
    Serial.print("\t");
    Serial.println(magnitude); // print magnitude value
    averageFrequency += magnitude;
  }
  
  averageFrequency /= (SAMPLES/2);
  Serial.print("Average Frequency: ");
  Serial.println(averageFrequency);
  LoRa. beginPacket();
  LoRa.print(averageFrequency);
  LoRa.endPacket();
  delay(10000); // wait for 10 seconds
}
