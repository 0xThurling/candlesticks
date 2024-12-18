#pragma once

#include "WeatherEntry.h"
#include <string>
#include <vector>

class Weather{
  public:
    Weather(std::string filename);

    /** Gets the weather entries for a region based on the filters */
    std::vector<WeatherEntry> getWeatherEntries(WeatherEntryType region, std::string timestamp);

    std::string getEarliestTime();

    std::string goToNextTimeFrame(std::string currentTime);
  private:
    std::vector<WeatherEntry> entryPoints;
};
