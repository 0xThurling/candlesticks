#pragma once

#include "WeatherEntry.h"
#include <vector>

// Class responsible for rendering weather data charts
class ChartRenderer {
private:
  // Maps array index to y-coordinate in the chart
  static double mapYCoordFromIndex(double index);

public:
  // Default constructor
  ChartRenderer();

  // Prints a graphical representation of weather data
  // @param yearly_entries Vector of vectors containing WeatherEntry objects
  static void printGraph(std::vector<std::vector<WeatherEntry>> yearly_entries);

  // Calculates points in linear space between two values
  // @param y1 Starting value
  // @param y2 Ending value
  // @param i Current position between y1 and y2
  static double linearSpace(double y1, double y2, double i);
};
