#include "Sender.h"

double findMax(double arr[]) {
  return *std::max_element(arr, arr+sample_n);
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

void removeBias(double arr[], double bias) { 
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
