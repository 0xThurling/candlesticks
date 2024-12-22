#include "Prediction.h"
#include "Candlestick.h"
#include <vector>

Prediction::Prediction(std::vector<Candlestick> candlestickData) {
  for (const Candlestick& entry : candlestickData) {
    data.push_back(entry.closingTemp);
  }
}

std::vector<double> Prediction::backshift(int k) {

  std::vector<double> result;

  if (k < data.size()) {
    // Add zeroes to the beginning
    result.insert(data.begin(), k, 0.0);

    result.insert(data.end(), data.begin(), data.end() - k);
  } else {
    // If K >= data.size(), return a vector of zeroes
    result.resize(data.size(), 0.0);
  }

  return result;
}
