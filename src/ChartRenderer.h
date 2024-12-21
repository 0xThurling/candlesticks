#pragma once

#include "WeatherEntry.h"
#include <vector>

class ChartRenderer {
  private:
    static double mapYCoordFromIndex(double index);
  
  public:
    ChartRenderer();

    static void printGraph(std::vector<std::vector<WeatherEntry>> yearly_entries);
};
