#pragma once

#include "WeatherEntry.h"
#include <vector>

class ChartRenderer {
  public:
    ChartRenderer();

    static void printGraph(std::vector<std::vector<WeatherEntry>> yearly_entries);
};
