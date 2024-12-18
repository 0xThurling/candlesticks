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

  auto t = std::find_if(entryPoints.begin(), entryPoints.end(), 
      [&currentYear](const WeatherEntry& entry){
        return entry.timeframe == std::to_string(currentYear++);
      });

  if (t == entryPoints.end()) {
    return getEarliestTime();
  }

  return std::to_string(currentYear++);
}
