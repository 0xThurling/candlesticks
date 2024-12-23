#pragma once

#include <string>
#include <vector>

#include "WeatherEntry.h"

// CSVReader class declaration
class CSVReader {
public:
  // Constructor
  CSVReader();

  // Static method to read a CSV file and return a vector of WeatherEntry
  // objects
  static std::vector<WeatherEntry> readCSV(std::string csvFile);

  // Static method to tokenize a CSV line into a vector of strings based on a
  // separator
  static std::vector<std::string> tokenise(std::string csvLine, char separator);

private:
  static std::vector<WeatherEntry>

  // Static method to convert a vector of strings to a vector of WeatherEntry
  // objects
  stringsToWE(std::vector<std::string> strings);
};
