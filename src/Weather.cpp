#include "Weather.h"
#include "CSVReader.h"
#include "WeatherEntry.h"

#include <algorithm>
#include <string>
#include <variant>
#include <vector>

Weather::Weather(std::string filename) {
  entryPoints = CSVReader::readCSV(filename);
}

// Focuses on yearly data for now
std::variant<std::vector<WeatherEntry>, std::vector<std::vector<WeatherEntry>>> Weather::getWeatherEntries(WeatherEntryType region,
                                                    std::string timestamp,
                                                    WeatherFilterOptions timeframe) 
{
  std::vector<WeatherEntry> filtered_entries;

  for (const WeatherEntry& entry : entryPoints) {
    if (entry.region == region &&
        entry.timeframe.find(timestamp) != std::string::npos) {
      filtered_entries.push_back(entry);
    }
  }


  std::vector<std::vector<WeatherEntry>> monthly_entries;


  // Only done when montly time period is selected - get the montly entries for a specific year
  if (timeframe == WeatherFilterOptions::monthly) {
    int month = 1;

    std::vector<WeatherEntry> monthly;

    while (month <= 12) {

      std::string month_string;

      if (month < 10) {
        month_string = "0" + std::to_string(month);
      } else {
        month_string = std::to_string(month);
      }
  
      std::string time = timestamp + "-" + month_string;

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

std::string Weather::getEarliestTime() {
  return entryPoints.begin()->timeframe;
}

std::string Weather::goToNextTimeFrame(std::string currentTime) {
  int currentYear = std::stoi(currentTime);
  
  currentYear++;

  auto t = std::find_if(entryPoints.begin(), entryPoints.end(), 
      [&currentYear](const WeatherEntry& entry){
        return entry.timeframe.find(std::to_string(currentYear)) != std::string::npos;
      });

  if (t != entryPoints.end()) {
    return t->timeframe;
  }

  return getEarliestTime();
}

double Weather::getHighestTemp(std::vector<WeatherEntry> &currentTimeEntries){
  double highestPrice = 0.0;

  for (const WeatherEntry& entry : currentTimeEntries) {
    if (entry.temp > highestPrice) {
      highestPrice = entry.temp;
    }
  }

  return highestPrice;
}

double Weather::getOpeningTemp(std::vector<WeatherEntry> &previousTimeEntries){
  double openingTemp = 0.0;

  for (const WeatherEntry& entry : previousTimeEntries) {
    openingTemp += entry.temp;
  }

  return openingTemp / previousTimeEntries.size();
}

double Weather::getClosingTemp(std::vector<WeatherEntry> &currentTimeEntries){
  double closingTemp = 0.0;

  for (const WeatherEntry& entry : currentTimeEntries) {
    closingTemp += entry.temp;
  }

  return closingTemp / currentTimeEntries.size();
}

double Weather::getLowestTemp(std::vector<WeatherEntry> &currentTimeEntries){
  double lowestTemp = 0.0;

  for (const WeatherEntry& entry : currentTimeEntries) {
    if (entry.temp < lowestTemp) {
      lowestTemp = entry.temp;
    }
  }

  return lowestTemp;
}
