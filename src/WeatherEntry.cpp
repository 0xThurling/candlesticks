#include "WeatherEntry.h"
#include <string>

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
  switch (input) {
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
