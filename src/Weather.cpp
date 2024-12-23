/**
 * Author: Jacques Thurling
 * Date: 2024-23-12
 * Notes: All code written without assistance
*/

/**
 * ===============================================
 * Code written by Jacques Thurling
 * ===============================================
*/

#include "Weather.h"
#include "CSVReader.h"
#include "WeatherEntry.h"

#include <algorithm>
#include <string>
#include <variant>
#include <vector>

/**
 * Trains the model by adjusting parameters to minimize prediction error
 * @param epochs Number of training iterations
 */
Weather::Weather(std::string filename) {
  entryPoints = CSVReader::readCSV(filename);
}

/**
 * Retrieves weather entries based on specified filters
 * @param region The geographic region to filter by
 * @param timestamp The time period to filter by
 * @param timeframe The granularity of data (yearly/monthly)
 * @return Either a vector of entries or a vector of monthly entry vectors
 */
std::variant<std::vector<WeatherEntry>, std::vector<std::vector<WeatherEntry>>>
Weather::getWeatherEntries(WeatherEntryType region, std::string timestamp,
                           WeatherFilterOptions timeframe) {
  // Filter entries by region and timestamp
  std::vector<WeatherEntry> filtered_entries;

  for (const WeatherEntry &entry : entryPoints) {
    if (entry.region == region &&
        entry.timeframe.find(timestamp) != std::string::npos) {
      filtered_entries.push_back(entry);
    }
  }

  std::vector<std::vector<WeatherEntry>> monthly_entries;

  // Only done when montly time period is selected - get the montly entries for
  // a specific year Handle monthly timeframe option
  if (timeframe == WeatherFilterOptions::monthly) {
    int month = 1;

    std::vector<WeatherEntry> monthly;

    // Collect entries for each month
    while (month <= 12) {
      // Format month string with leading zero if needed
      std::string month_string;
      if (month < 10) {
        month_string = "0" + std::to_string(month);
      } else {
        month_string = std::to_string(month);
      }

      std::string time = timestamp + "-" + month_string;

      // Filter entries for current month
      for (const WeatherEntry &entry : filtered_entries) {
        if (entry.region == region &&
            entry.timeframe.find(time) != std::string::npos) {
          monthly.push_back(entry);
        }
      }

      monthly_entries.push_back(monthly);

      month++;
    }

    return monthly_entries;
  }

  return filtered_entries;
}

/**
 * Gets the earliest timestamp in the dataset
 * @return String representing the earliest timestamp
 */
std::string Weather::getEarliestTime() {
  return entryPoints.begin()->timeframe;
}

/**
 * Advances to the next time period in the dataset
 * @param currentTime Current timestamp
 * @return Next available timestamp, or earliest if at end of dataset
 */
std::string Weather::goToNextTimeFrame(std::string currentTime) {
  int currentYear = std::stoi(currentTime);

  currentYear++;

  // Find next entry with incremented year
  auto t =
      std::find_if(entryPoints.begin(), entryPoints.end(),
                   [&currentYear](const WeatherEntry &entry) {
                     return entry.timeframe.find(std::to_string(currentYear)) !=
                            std::string::npos;
                   });

  if (t != entryPoints.end()) {
    return t->timeframe;
  }

  return getEarliestTime();
}

/**
 * Finds the highest temperature in a set of entries
 * @param currentTimeEntries Vector of weather entries to search
 * @return Highest temperature found
 */
double Weather::getHighestTemp(std::vector<WeatherEntry> &currentTimeEntries) {
  double highestPrice = 0.0;

  for (const WeatherEntry &entry : currentTimeEntries) {
    if (entry.temp > highestPrice) {
      highestPrice = entry.temp;
    }
  }

  return highestPrice;
}

/**
 * Calculates average opening temperature for a set of entries
 * @param previousTimeEntries Vector of weather entries
 * @return Average opening temperature
 */
double Weather::getOpeningTemp(std::vector<WeatherEntry> &previousTimeEntries) {
  double openingTemp = 0.0;

  for (const WeatherEntry &entry : previousTimeEntries) {
    openingTemp += entry.temp;
  }

  return openingTemp / previousTimeEntries.size();
}

/**
 * Calculates average closing temperature for a set of entries
 * @param currentTimeEntries Vector of weather entries
 * @return Average closing temperature
 */
double Weather::getClosingTemp(std::vector<WeatherEntry> &currentTimeEntries) {
  double closingTemp = 0.0;

  for (const WeatherEntry &entry : currentTimeEntries) {
    closingTemp += entry.temp;
  }

  return closingTemp / currentTimeEntries.size();
}

/**
 * Finds the lowest temperature in a set of entries
 * @param currentTimeEntries Vector of weather entries to search
 * @return Lowest temperature found
 */
double Weather::getLowestTemp(std::vector<WeatherEntry> &currentTimeEntries) {
  double lowestTemp = 0.0;

  for (const WeatherEntry &entry : currentTimeEntries) {
    if (entry.temp < lowestTemp) {
      lowestTemp = entry.temp;
    }
  }

  return lowestTemp;
}
/**
 * ===================================================
 *  End of written code section
 * ===================================================
*/


