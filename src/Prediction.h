#pragma once

#include "Candlestick.h"
#include <vector>
class Prediction {
  public:
    Prediction(std::vector<Candlestick> candlestickData);

    std::vector<double> backshift(std::vector<double>& data, int k = 1);

    std::vector<double> arComponent(std::vector<double>& data);

    std::vector<double> seasonalArComponent(std::vector<double>& data);

    std::vector<double> predict(int steps = 1);

    void fit(int epochs = 100);

    std::vector<double> data;
    double phi = 0.7;
    double PHI = 0.8;
    double learningRate = 0.01;
};
