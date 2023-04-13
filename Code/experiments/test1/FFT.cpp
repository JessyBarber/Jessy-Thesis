#include "Sender.h"

void deMean(double *axis_data) {
  double total = 0;
  for (int i = 0; i < sample_n; i++) {
    total += axis_data[i];
  }   
  total /= sample_n;
  for (int i = 0; i < sample_n; i++) {
    axis_data[i] -= total;
  }
}

double findMax(double arr[]) {
  return *std::max_element(arr, arr+sample_n);
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
  int maxIndex = 0;
  for (int i = 1; i < sample_n / 2; i++) { // Only need to search the first half of the array
    if (arr[i] > arr[maxIndex]) {
      maxIndex = i;
    }
  }
  return maxIndex;
}

// int findMaxIndex(double *v, double threshold) {
//   int maxIndex = 0;
//   double maxValue = v[0];

//   for (int i = 1; i < sample_n / 2; i++) {
//     if ((v[i] > maxValue) && (i * ((double)sample_rate / sample_n) > threshold)) {
//       maxValue = v[i];
//       maxIndex = i;
//     }
//   }
//   return maxIndex;
// }