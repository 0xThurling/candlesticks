#pragma once

#include "WeatherEntry.h"
#include <string>
#include <variant>
#include <vector>

// Enumeration for weather data filtering options
enum WeatherFilterOptions { yearly, monthly };

class Weather {
public:
  // Constructor that takes a filename containing weather data
  Weather(std::string filename);

  /** Gets the weather entries for a region based on the filters
   * Returns either a vector of entries or a vector of vector of entries
   * depending on the timeframe selected
   */
  std::variant<std::vector<WeatherEntry>,
               std::vector<std::vector<WeatherEntry>>>
  getWeatherEntries(WeatherEntryType region, std::string timestamp,
                    WeatherFilterOptions timeframe = yearly);

  // Returns the earliest timestamp in the dataset
  std::string getEarliestTime();

  // Advances to the next time period from the current timestamp
  std::string goToNextTimeFrame(std::string currentTime);

  // Static utility functions for temperature calculations
  static double getHighestTemp(std::vector<WeatherEntry> &currentTimeEntries);
  static double getLowestTemp(std::vector<WeatherEntry> &currentTimeEntries);
  static double getClosingTemp(std::vector<WeatherEntry> &currentTimeEntries);
  static double getOpeningTemp(std::vector<WeatherEntry> &previousTimeEntries);

private:
  std::vector<WeatherEntry> entryPoints;
};
