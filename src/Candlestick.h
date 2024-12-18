#pragma once

class Candlestick {
  public:
    Candlestick(double openingTemp, double closingTemp, double highestTemp, double lowestTemp);

    double openingTemp;
    double closingTemp;
    double highestTemp;
    double lowestTemp;
};
