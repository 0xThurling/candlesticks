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

  for (const Candlestick& c : candlesticks) {
    std::cout << "Highest: " << c.highestTemp << " Lowest: " << c.lowestTemp << " Opening: " << c.openingTemp << " Closing: " << c.closingTemp << std::endl;
  }

  std::cout << std::endl;

  int tolerance = 3;

  for (int i = 0; i < height; i++) {
    temp = mapYCoordFromIndex(i);
    for (int j = 0; j < width; j++) {
      if (j == 0 && i == height - 1) {
        std::cout << "    └";
      } else if (j == 0) {
        if ((i % 2) == 0) {
          // Prepare the y-axis
          if(temp < -10) {
            std::cout << temp << " ┤";
          } else if (temp < 10 && temp > -1) {
            std::cout << "  " << temp << " ┤";
          } else if (temp < -1 && temp > -10) {
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

            if (candlestick.highestTemp == candlestick.lowestTemp) {
              std::cout << " ";
            } else if (candlestick.openingTemp < candlestick.closingTemp) {
              if (temp < candlestick.highestTemp && temp > candlestick.closingTemp + tolerance) {
                std::cout << "│";
              } else if (temp < candlestick.closingTemp + tolerance 
                  && temp > candlestick.openingTemp - tolerance) {
                if (candlestick.closingTemp - candlestick.openingTemp < 1) {
                 std::cout << "┼";
                } else {
                 std::cout << "█";
                }
              } else if (temp < candlestick.openingTemp && temp > candlestick.lowestTemp) {
                std::cout << "│";
              }
            } else if (candlestick.closingTemp < candlestick.openingTemp) {
              if (temp < candlestick.highestTemp && temp > candlestick.openingTemp) {
                std::cout << "│";
              } else if (temp < candlestick.openingTemp && temp > candlestick.closingTemp) {
                std::cout << "█";
              } else if (temp < candlestick.closingTemp && temp > candlestick.lowestTemp) {
                std::cout << "│";
              }
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
