#include "Candlestick.h"
#include <iostream>

Candlestick::Candlestick(double openingTemp, double closingTemp,
                         double highestTemp, double lowestTemp)
    : openingTemp(openingTemp), closingTemp(closingTemp),
      highestTemp(highestTemp), lowestTemp(lowestTemp) {}

void Candlestick::printCandleStickChart(std::vector<Candlestick> &candlesticks){
  unsigned int height = 25;
  unsigned int width = 90;

  int temp = 40;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (j == 0 && i == height - 1) {
        std::cout << "    └";
      } else if (j == 0) {
        if ((i % 3) - 1 == 0) {
          if (temp < 0) {
            std::cout << temp << " ┤";
          } else if (temp == 0) {
            std::cout << "  " << temp << " ┤";
          } else {
            std::cout << " " << temp << " ┤";
          }
          temp -= 10;
        } else {
          std::cout << "    │";
        }
      } else if (i == height - 1) {
        std::cout << "─";
      }
    }
    std::cout << std::endl;
  }
}
