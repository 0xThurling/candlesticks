#include "Prediction.h"
#include "Candlestick.h"
#include <vector>

Prediction::Prediction(std::vector<Candlestick> candlestickData) {
  for (const Candlestick& entry : candlestickData) {
    data.push_back(entry.closingTemp);
  }
}

std::vector<double> Prediction::backshift(std::vector<double>& clonedData, int k) {

  std::vector<double> result;

  if (k < clonedData.size()) {
    // Add zeroes to the beginning
    result.insert(clonedData.begin(), k, 0.0);

    result.insert(clonedData.end(), clonedData.begin(), clonedData.end() - k);
  } else {
    // If K >= data.size(), return a vector of zeroes
    result.resize(clonedData.size(), 0.0);
  }

  return result;
}

std::vector<double> Prediction::arComponent(std::vector<double>& clonedData) {
  std::vector<double> shifted = backshift(clonedData);

  std::vector<double> result;

  for (int i = 0; i < clonedData.size(); i++) {
    result.push_back(shifted[i] * phi);
  } 

  return result;
}

std::vector<double> Prediction::seasonalArComponent(std::vector<double>& clonedData) {
  std::vector<double> shifted = backshift(clonedData, 1);

  std::vector<double> result;

  for (int i = 0; i < clonedData.size(); i++) {
    result.push_back(shifted[i] * PHI);
  } 

  return result;
}

std::vector<double> Prediction::predict(int steps){
  std::vector<double> predictions;
  std::vector<double> working_data = data;

  // Loop without index needed
  for (int _ = 0; _ < steps; _++) {
    double ar = arComponent(working_data)[working_data.size() - 1];
    double seasonalAr = seasonalArComponent(working_data)[working_data.size() - 1];

    double nextValue = ar + seasonalAr;
    predictions.push_back(nextValue);
    working_data.push_back(nextValue);
  }

  return predictions;
}

void Prediction::fit(int epochs) {
  for (int _ = 0; _ < epochs; _++) {
    std::vector<double> prediction = predict(1);
    double error = prediction[0] - data[data.size() - 1];

    phi -= learningRate * error * data[data.size() - 2];
    PHI -= learningRate * error * data[data.size() - 1];
  }
}
