#pragma once

#include "Candlestick.h"
#include <vector>
class Prediction {
  public:
    Prediction(std::vector<Candlestick> candlestickData);

    std::vector<double> backshift(int k = 1);

    std::vector<double> data;
    double phi = 0.7;
    double PHI = 0.8;
    double learningRate = 0.01;
};
