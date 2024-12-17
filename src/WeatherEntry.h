#pragma once

#include <string>

enum class WeatherEntryType{AT, BE, BG, CH, CZ, DE, DK, EE, ES, FI, FR, GB, GR, HR, IE, IT, LT, LU, LV, NL, NO, PL, PT, RO, SE, SI, SK};

class WeatherEntry {
  public:
    WeatherEntry(double temp, std::string timeframe, WeatherEntryType region);

    static WeatherEntryType mapFromTokenToRegion(int index);

    double temp;
    std::string timeframe;
    WeatherEntryType region;
};
