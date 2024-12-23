/**
 * Author: Jacques Thurling
 * Date: 2024-23-12
 * Notes: Used the main CSVReader from the original MerkelMain project given for us to use
 * and updated it using the new WeatherEntry object instead of the OrderBookEntry
*/

#include "CSVReader.h"
#include "WeatherEntry.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Constructor for CSVReader class
CSVReader::CSVReader() {}

// Method to read a CSV file and return a vector of WeatherEntry objects
std::vector<WeatherEntry> CSVReader::readCSV(std::string csvFilename) {
  // Vector to store WeatherEntry objects
  std::vector<WeatherEntry> entries;
  // Open CSV file
  std::ifstream csvFile{csvFilename};
  // String to store each line of the CSV file
  std::string line;
  // Log Message
  std::cout << "Loading file data" << std::endl;

  // Check if the file is open
  if (csvFile.is_open()) {
    // Read each line of the file
    while (std::getline(csvFile, line)) {
      try {
        // Tokenise the line and convert to WeatherEntry objects
        std::vector<WeatherEntry> woe = stringsToWE(tokenise(line, ','));
        for (const WeatherEntry &entry : woe) {
          // Add each WeatherEntry to the entries vector
          entries.push_back(entry);
        }
      } catch (const std::exception &e) {
        // Log Message for bad data
        std::cout << "CSVReader::readCSV bad data" << std::endl;
      }
    } // end of while
  }

  std::cout << "CSVReader::readCSV read " << entries.size() << " entries"
            << std::endl;
  // Return the vector of WeatherEntry objects
  return entries;
}

// Method to tokenise a CSV line into a vector of string based on a separator
std::vector<std::string> CSVReader::tokenise(std::string csvLine,
                                             char separator) {
  // Vector to store tokens
  std::vector<std::string> tokens;
  // Variables to store start and end positions of tokens
  signed int start, end;
  // String to store each token
  std::string token;
  // Fine the first non-seporator character
  start = csvLine.find_first_not_of(separator, 0);
  do {
    // Find the next separator char
    end = csvLine.find_first_of(separator, start);
    // Break if end of line or no more
    if (start == csvLine.length() || start == end)
      break;
    // Extract the token
    if (end >= 0)
      token = csvLine.substr(start, end - start);
    // Extract the last token
    else
      token = csvLine.substr(start, csvLine.length() - start);
    // Add the token to the vector
    tokens.push_back(token);
    // Update the start position
    start = end + 1;
  } while (end > 0);

  // Return the vector of tokens
  return tokens;
}

/**
* ================================================
* Code written by Jacques Thurling
* ================================================
*/

// Method to convert a vector of strings to a vector of WeatherEntry objects
std::vector<WeatherEntry>
CSVReader::stringsToWE(std::vector<std::string> strings) {
  // Vector to store WeatherEntry objects
  std::vector<WeatherEntry> entries;

  for (int i = 1; i < strings.size(); i++) {
    try {
      // Map token to region
      WeatherEntryType region = WeatherEntry::mapFromTokenToRegion(i);
      // Convert string to double for temperature
      double temperature = std::stod(strings[i]);
      // Get the timeframe
      std::string timeframe = strings[0];

      // Create Weather Entry object
      WeatherEntry entry{temperature, timeframe, region};
      // Add the WeatherEntry object to the vector
      entries.push_back(entry);
    } catch (const std::exception &e) {
      // Skip bat data
      continue;
    }
  }

  // Return the vector of WeatherEntry objects
  return entries;
}
/**
 * ===================================================
 *  End of written code section
 * ===================================================
*/


