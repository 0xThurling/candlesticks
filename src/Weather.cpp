#include "Weather.h"
#include "CSVReader.h"
#include "WeatherEntry.h"

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
    
}
