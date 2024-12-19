#include "Candlestick.h"
#include <iostream>

Candlestick::Candlestick(double openingTemp, double closingTemp,
                         double highestTemp, double lowestTemp)
    : openingTemp(openingTemp), closingTemp(closingTemp),
      highestTemp(highestTemp), lowestTemp(lowestTemp) {}

void Candlestick::printCandleStickChart(std::vector<Candlestick> &candlesticks){
  unsigned int height = 25;
  unsigned int width = 90;

  int temp = 50;

  int highest = 35;
  int opening = 23;
  int closing = 5;
  int lowest = -10;

  for (int i = 0; i < height; i++) {
    temp = mapYCoordFromIndex(i);
    for (int j = 0; j < width; j++) {
      if (j == 0 && i == height - 1) {
        std::cout << "    └";
      } else if (j == 0) {
        if ((i % 3) == 0) {
          // Prepare the y-axis
          if(temp < -12) {
            std::cout << temp << " ┤";
          } else if (temp < 10 && temp > -1) {
            std::cout << "  " << temp << " ┤";
          } else if (temp < -1 && temp > -12) {
            std::cout << " " << temp << " ┤";
          } else {
            std::cout << " " << temp << " ┤";
          }
        } else {
          std::cout << "    │";
        }
      } else if (i == height - 1) {
        // Populate the x-axis
        if (j % 10 == 0) {
          std::cout << "┬";
        } else {
          std::cout << "─";
        }
      } else {
          if (j % 10 == 0) {

            Candlestick candlestick = candlesticks[(j/10) - 1];

            std::cout << candlestick.lowestTemp;

            if (temp < highest && temp > opening) {
              std::cout << "│";
            } else if (temp < opening && temp > closing - 3) {
              std::cout << "█";
            } else if (temp < closing && temp > lowest) {
              std::cout << "│";
            }
          } else {
            std::cout << " ";
          }
      }
    }
    std::cout << std::endl;
  }
}

double Candlestick::mapYCoordFromIndex(int index){
  return 40 - ((80 * index)/25);
}
