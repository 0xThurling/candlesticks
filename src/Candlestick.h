#pragma once

#include <vector>
class Candlestick {
  private:
    static double mapYCoordFromIndex(int index);
  public:
    Candlestick(double openingTemp, double closingTemp, double highestTemp, double lowestTemp);

    static void printCandleStickChart(std::vector<Candlestick>& candlesticks);

    double openingTemp;
    double closingTemp;
    double highestTemp;
    double lowestTemp;
};
