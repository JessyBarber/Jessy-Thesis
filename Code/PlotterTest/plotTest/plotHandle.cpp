#include "plotter.h"

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