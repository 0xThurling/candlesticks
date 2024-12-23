/**
 * Author: Jacques Thurling
 * Date: 2024-23-12
 * Notes: All code written without assistance
*/

/**
 * ==========================================
 * Code written by Jacques Thurling
 * ==========================================
*/

#pragma once

#include <map>
#include <string>

// Enumeration for European country/region codes
enum class WeatherEntryType {
  AT,
  BE,
  BG,
  CH,
  CZ,
  DE,
  DK,
  EE,
  ES,
  FI,
  FR,
  GB,
  GR,
  HR,
  IE,
  IT,
  LT,
  LU,
  LV,
  NL,
  NO,
  PL,
  PT,
  RO,
  SE,
  SI,
  SK
};

// Class representing a single weather data entry
class WeatherEntry {
public:
  // Constructor to initialize a weather entry with temperature, timeframe and
  // region
  WeatherEntry(double temp, std::string timeframe, WeatherEntryType region);

  // Maps numeric index to corresponding region enum
  static WeatherEntryType mapFromTokenToRegion(int index);

  // Maps string input to corresponding region enum
  static WeatherEntryType mapFromInputToRegion(std::string input);

  double temp;
  std::string timeframe;
  WeatherEntryType region;

  // Static map to convert string representations to region enums
  static const std::map<std::string, WeatherEntryType> weatherRegionMap;
};
/**
 * ===================================================
 *  End of written code section
 * ===================================================
*/


