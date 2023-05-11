#include "Sender.h"

// double findMax(double arr[]) {
//   return *std::max_element(arr, arr+sample_n);
// }

double thresholdX = 0, thresholdY = 0, thresholdZ = 0;

double findMaxAbs(const double data[]) {
  double maxVal = 0;
  for (int i = 0; i < sample_n; ++i) {
    double absVal = abs(data[i]);
    if (absVal > maxVal) {
      maxVal = absVal;
    }
  }
  return maxVal;
}

void addGravity(double arr[]) {
  for (int i = 0; i < sample_n; i++) {
    arr[i] *= g;
  }
}

// void lowPassFilter(double *input, double *output, int windowSize) {
//   for (int i = 0; i < sample_n; i++) {
//     output[i] = 0;
//     int count = 0;
//     for (int j = i - windowSize; j <= i + windowSize; j++) {
//       if (j >= 0 && j < sample_n) {
//         output[i] += input[j];
//         count++;
//       }
//     }
//     output[i] /= count;
//   }
// }

// void lowPassFilter(double arr[]) {
//   double sum = 0;

//   for (uint16_t i = 0; i < window_size; ++i) {
//     sum += arr[i];
//   }

//   for (uint16_t i = window_size; i < sample_n; ++i) {
//     sum = sum - arr[i - window_size] + arr[i];
//     arr[i - window_size / 2] = sum / window_size;
//   }

//   for (uint16_t i = sample_n - window_size / 2; i < sample_n; ++i) {
//     arr[i] = arr[sample_n - window_size / 2 - 1];
//   }
// }

void lowPassFilter(double *data) {
  double filteredData = data[0]; // Initialize with the first value of the data array

  for (uint16_t i = 1; i < sample_n; i++) {
    filteredData = LP_alpha * data[i] + (1.0 - LP_alpha) * filteredData;
    data[i] = filteredData;
  }
}

void highPassFilter(double *data) {
  double filteredData = data[0]; // Initialize with the first value of the data array
  double prevRawData = data[0]; // Keep track of the previous raw data value

  for (uint16_t i = 1; i < sample_n; i++) {
    filteredData = HP_alpha * filteredData + HP_alpha * (data[i] - prevRawData);
    prevRawData = data[i];
    data[i] = filteredData;
  }
}

int findMaxIndex(double arr[]) {
  int maxIndex = 1;
  for (int i = 1; i < sample_n / 2; i++) { // Only need to search the first half of the array
    if (arr[i] > arr[maxIndex]) {
      maxIndex = i;
    }
  }
  return maxIndex;
}

double findAvg(double arr[]) {
  double sum = 0.0;
  for (int i = 0; i < sample_n; i++) {
    sum += arr[i];
  }
  return sum / sample_n;
}

void removeBias(double arr[]) { 
  double bias = findAvg(arr);
  for (int i = 0; i < sample_n; i++) {
    arr[i] -= bias;
  }
}

void integrate(const double arr[], double dt, double integrated[]) {
  double sum = 0.0;
  for (int i = 0; i < sample_n; i++) {
    sum += arr[i] * dt;
    integrated[i] = sum;
  }
}

void readRawData(double real_x_axis[], double real_y_axis[], double real_z_axis[]) {
  for (int i = 0; i < sample_n; i++) {
    // READ RAW DATA FROM ANALOG PINS
    real_x_axis[i] = analogRead(x_axis);
    real_y_axis[i] = analogRead(y_axis);
    real_z_axis[i] = analogRead(z_axis);
    // SAMPLING INTERVAL
    delay(sample_interval);
  }
}

void processRawData(double xAccel[], double yAccel[], double zAccel[], 
                    const double real_x_axis[], const double real_y_axis[], 
                    const double real_z_axis[], double xZero, double yZero, double zZero) {
  for (int i = 0; i < sample_n; i++) {
    // CONVERT ADC LEVEL TO A VOLTAGE
    double voltageX = ((real_x_axis[i] * vRef) / (adc_resolution - 1));
    double voltageY = ((real_y_axis[i] * vRef) / (adc_resolution - 1));
    double voltageZ = ((real_z_axis[i] * vRef) / (adc_resolution - 1));

    xAccel[i] = ((voltageX - vRef / 2) / sensitivity - xZero) * g;
    yAccel[i] = ((voltageY - vRef / 2) / sensitivity - yZero) * g;
    zAccel[i] = ((voltageZ - vRef / 2) / sensitivity - zZero - 1) * g; // Subtract gravity

    // // Apply threshold to remove noise
    xAccel[i] = (abs(xAccel[i]) <= 0.7) ? 0 : xAccel[i];
    yAccel[i] = (abs(yAccel[i]) <= 0.9) ? 0 : yAccel[i];
    zAccel[i] = (abs(zAccel[i]) <= 0.1) ? 0 : zAccel[i];
    // Update thresholds with exponential moving average
    // thresholdX = alpha * abs(xAccel[i]) + (1 - alpha) * thresholdX;
    // thresholdY = alpha * abs(yAccel[i]) + (1 - alpha) * thresholdY;
    // thresholdZ = alpha * abs(zAccel[i]) + (1 - alpha) * thresholdZ;

    // // Apply threshold to remove noise
    // xAccel[i] = (abs(xAccel[i]) <= thresholdX) ? 0 : xAccel[i];
    // yAccel[i] = (abs(yAccel[i]) <= thresholdY) ? 0 : yAccel[i];
    // zAccel[i] = (abs(zAccel[i]) <= thresholdZ) ? 0 : zAccel[i];
  }
}

void integrate(const double xIn[], const double yIn[], const double zIn[],
                      double xOut[], double yOut[], double zOut[]) {
  double dt = sample_interval / 1000; // sampl_interval back into seconds
  for(int i = 1; i < sample_n; ++i) {
    xOut[i] = xOut[i - 1] + 0.5 * (xIn[i] + xIn[i - 1]) * dt;
    yOut[i] = yOut[i - 1] + 0.5 * (yIn[i] + yIn[i - 1]) * dt;
    zOut[i] = zOut[i - 1] + 0.5 * (zIn[i] + zIn[i - 1]) * dt;
  }
}

void checkNan(double& freq) {
 if (isnan(freq)) {
  freq = 0;
 }
}