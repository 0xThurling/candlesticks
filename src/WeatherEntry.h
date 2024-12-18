#pragma once

#include <map>
#include <string>

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

class WeatherEntry {
  public:
    WeatherEntry(double temp, std::string timeframe, WeatherEntryType region);

    static WeatherEntryType mapFromTokenToRegion(int index);

    static WeatherEntryType mapFromInputToRegion(std::string input);

    double temp;
    std::string timeframe;
    WeatherEntryType region;

    std::map<std::string, WeatherEntryType> weatherRegionMap = {
      {"AT", WeatherEntryType::AT},
      {"BE", WeatherEntryType::BE},
      {"BG", WeatherEntryType::BG},
      {"CH", WeatherEntryType::CH},
      {"CZ", WeatherEntryType::CZ},
      {"DE", WeatherEntryType::DE},
      {"DK", WeatherEntryType::DK},
      {"EE", WeatherEntryType::EE},
      {"ES", WeatherEntryType::ES},
      {"FI", WeatherEntryType::FI},
      {"FR", WeatherEntryType::FR},
      {"GB", WeatherEntryType::GB},
      {"GR", WeatherEntryType::GR},
      {"HR", WeatherEntryType::HR},
      {"IE", WeatherEntryType::IE},
      {"IT", WeatherEntryType::IT},
      {"LT", WeatherEntryType::LT},
      {"LU", WeatherEntryType::LU},
      {"LV", WeatherEntryType::LV},
      {"NL", WeatherEntryType::NL},
      {"NO", WeatherEntryType::NO},
      {"PL", WeatherEntryType::PL},
      {"PT", WeatherEntryType::PT},
      {"RO", WeatherEntryType::RO},
      {"SE", WeatherEntryType::SE},
      {"SI", WeatherEntryType::SI},
      {"SK", WeatherEntryType::SK}
    };
};
