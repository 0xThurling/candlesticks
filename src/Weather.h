#pragma once

#include "WeatherEntry.h"
#include <string>
#include <variant>
#include <vector>

enum WeatherFilterOptions {
  yearly,
  monthly
};

class Weather{
  public:
    Weather(std::string filename);

    /** Gets the weather entries for a region based on the filters */
    std::variant<std::vector<WeatherEntry>,
                 std::vector<std::vector<WeatherEntry>>>
    getWeatherEntries(WeatherEntryType region, std::string timestamp,
                      WeatherFilterOptions timeframe = yearly);

    std::string getEarliestTime();

    std::string goToNextTimeFrame(std::string currentTime);

    static double getHighestTemp(std::vector<WeatherEntry>& currentTimeEntries);
    static double getLowestTemp(std::vector<WeatherEntry>& currentTimeEntries);
    static double getClosingTemp(std::vector<WeatherEntry>& currentTimeEntries);
    static double getOpeningTemp(std::vector<WeatherEntry>& previousTimeEntries);

  private:
    std::vector<WeatherEntry> entryPoints;
};
