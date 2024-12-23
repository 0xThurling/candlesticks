/**
 * Author: Jacques Thurling
 * Date: 2024-23-12
 * Notes: All code written without assistance
*/

/**
 * ===============================================
 * Code written by Jacques Thurling
 * ===============================================
*/

#pragma once

#include "Candlestick.h"
#include <vector>
class Prediction {
public:
  // Constructor that initializes prediction model with historical candlestick
  // data
  Prediction(std::vector<Candlestick> candlestickData);

  // Shifts data vector back by k positions, used for creating lagged features
  // Returns: vector shifted by k positions with zeros at the start
  std::vector<double> backshift(std::vector<double> data, int k = 1);

  // Calculates the autoregressive (AR) component of the time series
  // Returns: AR component of the time series
  std::vector<double> arComponent(std::vector<double> data);

  // Calculates the seasonal autoregressive component of the time series
  // Returns: Seasonal AR component of the time series
  std::vector<double> seasonalArComponent(std::vector<double> data);

  // Makes future predictions for specified number of steps
  // Returns: Vector of predicted values
  std::vector<double> predict(int steps = 1);

  // Trains the model parameters using gradient descent
  // epochs: Number of training iterations
  void fit(int epochs = 100);

  // Time series data
  std::vector<double> data;
  // AR coefficient for regular component
  double phi = 0.7;
  // AR coefficient for seasonal component
  double PHI = 0.8;
  // Learning rate for gradient descent optimization
  double learningRate = 0.01;
};
/**
 * ===================================================
 *  End of written code section
 * ===================================================
*/


