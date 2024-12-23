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

#include "Prediction.h"
#include "Candlestick.h"
#include <vector>

/**
 * Constructor: Initializes prediction model with historical candlestick data
 * @param candlestickData Vector of historical temperature data points
 */
Prediction::Prediction(std::vector<Candlestick> candlestickData) {
  for (const Candlestick& entry : candlestickData) {
    data.push_back(entry.closingTemp);
  }
}

/**
 * Shifts data backwards by k positions, filling with zeros
 * @param clonedData Input data vector to shift
 * @param k Number of positions to shift
 * @return Vector with shifted data
 */
std::vector<double> Prediction::backshift(std::vector<double> clonedData, int k) {

  std::vector<double> result;

  if (k < clonedData.size()) {
    // Add zeroes to the beginning
    result.insert(result.begin(), k, 0.0);

    // Add data[:-k]
    result.insert(result.end(), clonedData.begin(), clonedData.end() - k);
  } else {
    // If K >= data.size(), return a vector of zeroes
    result.resize(clonedData.size(), 0.0);
  }

  return result;
}

/**
 * Calculates the autoregressive (AR) component of the prediction
 * @param clonedData Input data vector
 * @return Vector containing AR components
 */
std::vector<double> Prediction::arComponent(std::vector<double> clonedData) {
  std::vector<double> shifted = backshift(clonedData);

  std::vector<double> result;

  for (int i = 0; i < clonedData.size(); i++) {
    result.push_back(shifted[i] * phi);
  } 

  return result;
}

/**
 * Calculates the seasonal autoregressive component of the prediction
 * @param clonedData Input data vector
 * @return Vector containing seasonal AR components
 */
std::vector<double> Prediction::seasonalArComponent(std::vector<double> clonedData) {
  std::vector<double> shifted = backshift(clonedData, 1);

  std::vector<double> result;

  for (int i = 0; i < clonedData.size(); i++) {
    result.push_back(shifted[i] * PHI);
  } 

  return result;
}

/**
 * Generates future predictions based on historical data
 * @param steps Number of future steps to predict
 * @return Vector of predicted values
 */
std::vector<double> Prediction::predict(int steps){
  std::vector<double> predictions;
  std::vector<double> working_data = data;

  // Loop without index needed
  // Generate predictions for specified number of steps
  for (int _ = 0; _ < steps; _++) {
    double ar = arComponent(working_data).back();
    double seasonalAr = seasonalArComponent(working_data).back();

    double nextValue = ar + seasonalAr;
    predictions.push_back(nextValue);
    working_data.push_back(nextValue);
  }

  return predictions;
}

/**
 * Trains the model by adjusting parameters to minimize prediction error
 * @param epochs Number of training iterations
 */
void Prediction::fit(int epochs) {
  for (int _ = 0; _ < epochs; _++) {
    std::vector<double> prediction = predict(1);
 
    double error = prediction[0] - data[data.size() - 1];

    phi -= learningRate * error * data[data.size() - 2];
    PHI -= learningRate * error * data[data.size() - 1];
  }
}
/**
 * ===================================================
 *  End of written code section
 * ===================================================
*/


