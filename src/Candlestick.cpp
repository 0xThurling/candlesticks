/**
 * Author: Jacques Thurling
 * Date: 2024-23-12
 * Notes: All code written without assistance
*/

/**
 * ============================================
 * Code written by Jacques Thurling
 * ============================================
*/

#include "Candlestick.h"
#include <iostream>

// Constructor initializes a candlestick with opening, closing, highest, and
// lowest temperatures
Candlestick::Candlestick(double openingTemp, double closingTemp,
                         double highestTemp, double lowestTemp)
    : openingTemp(openingTemp), closingTemp(closingTemp),
      highestTemp(highestTemp), lowestTemp(lowestTemp) {}

// Prints an ASCII art candlestick chart using the provided vector of
// candlesticks
void Candlestick::printCandleStickChart(
    std::vector<Candlestick> &candlesticks) {
  // Chart height in characters
  unsigned int height = 25;
  // Chart width in characters
  unsigned int width = 130;

  // Initial temperature values for y-axis
  int temp = 50;

  std::cout << std::endl;

  // Temperature tolerance for drawing candlesticks
  int tolerance = 3;

  std::cout << "                                                            Monthly Temperatures" << std::endl;

  // Iterate through each row of the chart
  for (int i = 0; i < height; i++) {
    // Map row index to temperature values
    temp = mapYCoordFromIndex(i);

    // Iterate though each column
    for (int j = 0; j < width; j++) {
      if (j == 0 && i == height - 1) {
        // Bottom left corner
        std::cout << "    └";
      } else if (j == 0) {
        if ((i % 2) == 0) {
          // Prepare the y-axis
          if (temp < -10) {
            std::cout << temp << " ┤";
          } else if (temp < 10 && temp > -1) {
            std::cout << "  " << temp << " ┤";
          } else if (temp < -1 && temp > -10) {
            std::cout << " " << temp << " ┤";
          } else {
            std::cout << " " << temp << " ┤";
          }
        } else {
          // Y-axis line
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
          
          Candlestick candlestick = candlesticks[(j / 10) - 1];

          // Draw candlestick components based on temperature relationships
          if (candlestick.highestTemp == candlestick.lowestTemp) {
            // No variation in temperatures
            std::cout << " ";
          } else if (candlestick.openingTemp < candlestick.closingTemp) {
            SetColour(32);
            // Bullish candlestick (closing > opening)
            if (temp < candlestick.highestTemp &&
                temp > candlestick.closingTemp + tolerance) {
              std::cout << "│";
            } else if (temp < candlestick.closingTemp + tolerance &&
                       temp > candlestick.openingTemp - tolerance) {
              if (candlestick.closingTemp - candlestick.openingTemp < 1) {
                std::cout << "┼";
              } else {
                std::cout << "█";
              }
            } else if (temp < candlestick.openingTemp &&
                       temp > candlestick.lowestTemp) {
              std::cout << "│";
            } else {
              std::cout << " ";
            }

            ResetColour();
          } else if (candlestick.closingTemp < candlestick.openingTemp) {
            SetColour(31);

            // Bearish candlestick (closing < opening)
            if (temp < candlestick.highestTemp &&
                temp > candlestick.openingTemp) {
              std::cout << "│";
            } else if (temp < candlestick.openingTemp &&
                       temp > candlestick.closingTemp) {
              std::cout << "█";
            } else if (temp < candlestick.closingTemp &&
                       temp > candlestick.lowestTemp) {
              std::cout << "│";
            } else {
              std::cout << " ";
            }

            ResetColour();
          } else {
            std::cout << " ";
          }

        } else {
          std::cout << " ";
        }
      }
    }
    std::cout << std::endl;
  }

  std::cout << "     ";
  for (int i = 0; i < 12; i++) {
    if (i + 1 > 9) {
      std::cout << "        " << (i + 1);
    } else {
      std::cout << "         " << (i + 1);
    }
  }
  std::cout << std::endl;
}

// Set the colour for the chart
void Candlestick::SetColour(int textColor) {
    std::cout << "\033[" << textColor << "m";
}

// Resets the terminal colour
void Candlestick::ResetColour() {
    std::cout << "\033[0m";
}

// Maps a y-coordinate index to a temperature value
// This creates the temperature scale on the y-axis
double Candlestick::mapYCoordFromIndex(int index) {
  return 40 - ((80 * index) / 25);
}
/**
 * ===================================================
 *  End of written code section
 * ===================================================
*/
