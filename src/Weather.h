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

    static double getHighestTemp(std::vector<WeatherEntry>& currentTimeEntries);
    static double getLowestTemp(std::vector<WeatherEntry>& currentTimeEntries);
    static double getClosingTemp(std::vector<WeatherEntry>& currentTimeEntries);
    static double getOpeningTemp(std::vector<WeatherEntry>& previousTimeEntries);

  private:
    std::vector<WeatherEntry> entryPoints;
};
