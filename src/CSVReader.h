/**
 * Author: Jacques Thurling
 * Date: 2024-23-12
 * Notes: Used the main CSVReader from the original MerkelMain project given for us to use
 * and updated it using the new WeatherEntry object instead of the OrderBookEntry
*/


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

  /**
   * ===================================================
   * Code written by Jacques Thurling
   * ===================================================
  */

  static std::vector<WeatherEntry>

  // Static method to convert a vector of strings to a vector of WeatherEntry
  // objects
  stringsToWE(std::vector<std::string> strings);

  /**
   * ===================================================
   *  End of written code section
   * ===================================================
  */
};


