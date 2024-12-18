#include "Weather.h"
#include "CSVReader.h"
#include "WeatherEntry.h"

#include <algorithm>
#include <string>
#include <vector>

Weather::Weather(std::string filename) {
  entryPoints = CSVReader::readCSV(filename);
}

// Focuses on yearly data for now
std::vector<WeatherEntry> Weather::getWeatherEntries(WeatherEntryType region,
                                                    std::string timeframe) 
{
  std::vector<WeatherEntry> filtered_entries;

  for (const WeatherEntry& entry : entryPoints) {
    if (entry.region == region &&
        entry.timeframe.find(timeframe) != std::string::npos) {
      filtered_entries.push_back(entry);
    }
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
