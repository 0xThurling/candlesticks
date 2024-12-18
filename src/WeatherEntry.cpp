#include "WeatherEntry.h"
#include <algorithm>
#include <cctype>
#include <string>

static const std::map<std::string, WeatherEntryType> weatherRegionMap = {
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

WeatherEntry::WeatherEntry(double temp, std::string timeframe, WeatherEntryType region)
  : temp(temp), timeframe(timeframe), region(region)
{}

WeatherEntryType WeatherEntry::mapFromTokenToRegion(int index){
  switch (index) {
    case 1: return WeatherEntryType::AT; break;
    case 2: return WeatherEntryType::BE; break;
    case 3: return WeatherEntryType::BG; break;
    case 4: return WeatherEntryType::CH; break;
    case 5: return WeatherEntryType::CZ; break;
    case 6: return WeatherEntryType::DE; break;
    case 7: return WeatherEntryType::DK; break;
    case 8: return WeatherEntryType::EE; break;
    case 9: return WeatherEntryType::ES; break;
    case 10: return WeatherEntryType::FI; break;
    case 11: return WeatherEntryType::FR; break;
    case 12: return WeatherEntryType::GB; break;
    case 13: return WeatherEntryType::GR; break;
    case 14: return WeatherEntryType::HR; break;
    case 15: return WeatherEntryType::IE; break;
    case 16: return WeatherEntryType::IT; break;
    case 17: return WeatherEntryType::LT; break;
    case 18: return WeatherEntryType::LU; break;
    case 19: return WeatherEntryType::LV; break;
    case 20: return WeatherEntryType::NL; break;
    case 21: return WeatherEntryType::NO; break;
    case 22: return WeatherEntryType::PL; break;
    case 23: return WeatherEntryType::PT; break;
    case 24: return WeatherEntryType::RO; break;
    case 25: return WeatherEntryType::SE; break;
    case 26: return WeatherEntryType::SI; break;
    case 27: return WeatherEntryType::SK; break;
  }
}

WeatherEntryType WeatherEntry::mapFromInputToRegion(std::string input){

  std::transform(input.begin(), input.end(), input.begin(), ::toupper);

  switch (weatherRegionMap.at(input)) {
    case WeatherEntryType::AT: return WeatherEntryType::AT; break;
    case WeatherEntryType::BE: return WeatherEntryType::BE; break;
    case WeatherEntryType::BG: return WeatherEntryType::BG; break;
    case WeatherEntryType::CH: return WeatherEntryType::CH; break;
    case WeatherEntryType::CZ: return WeatherEntryType::CZ; break;
    case WeatherEntryType::DE: return WeatherEntryType::DE; break;
    case WeatherEntryType::DK: return WeatherEntryType::DK; break;
    case WeatherEntryType::EE: return WeatherEntryType::EE; break;
    case WeatherEntryType::ES: return WeatherEntryType::ES; break;
    case WeatherEntryType::FI: return WeatherEntryType::FI; break;
    case WeatherEntryType::FR: return WeatherEntryType::FR; break;
    case WeatherEntryType::GB: return WeatherEntryType::GB; break;
    case WeatherEntryType::GR: return WeatherEntryType::GR; break;
    case WeatherEntryType::HR: return WeatherEntryType::HR; break;
    case WeatherEntryType::IE: return WeatherEntryType::IE; break;
    case WeatherEntryType::IT: return WeatherEntryType::IT; break;
    case WeatherEntryType::LT: return WeatherEntryType::LT; break;
    case WeatherEntryType::LU: return WeatherEntryType::LU; break;
    case WeatherEntryType::LV: return WeatherEntryType::LV; break;
    case WeatherEntryType::NL: return WeatherEntryType::NL; break;
    case WeatherEntryType::NO: return WeatherEntryType::NO; break;
    case WeatherEntryType::PL: return WeatherEntryType::PL; break;
    case WeatherEntryType::PT: return WeatherEntryType::PT; break;
    case WeatherEntryType::RO: return WeatherEntryType::RO; break;
    case WeatherEntryType::SE: return WeatherEntryType::SE; break;
    case WeatherEntryType::SI: return WeatherEntryType::SI; break;
    case WeatherEntryType::SK: return WeatherEntryType::SK; break;
  }
}
