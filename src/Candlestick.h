/**
 * Author: Jacques Thurling
 * Date: 2024-23-12
 * Notes: All code written without assistance
*/

/**
 * ====================================================
 * Code written by Jacques Thurling
 * ====================================================
*/


#pragma once

#include <vector>

// The Candlestick class represents a single candlestick in a candlestick chart,
// which is commonly used in financial analysis to represent the price movements
// of a security over a specific period of time, however for this use case it is
// used to determine the movement of weather temperature over time.
class Candlestick {
private:
  // Maps a Y-coordinate from an index. This is a static helper function.
  static double mapYCoordFromIndex(int index);

  static void SetColour(int textColour);

  static void ResetColour();
public:
  // Constructor to initialize a Candlestick object with the given temperatures.
  Candlestick(double openingTemp, double closingTemp, double highestTemp,
              double lowestTemp);

  // Static function to print the candlestick chart from a vector of Candlestick
  // objects.
  static void printCandleStickChart(std::vector<Candlestick> &candlesticks);

  // Member variables representing the opening, closing, highest, and lowest
  // temperatures.
  double openingTemp;
  double closingTemp;
  double highestTemp;
  double lowestTemp;
};
/**
 * ===================================================
 *  End of written code section
 * ===================================================
*/


