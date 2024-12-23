#pragma once

#include "Candlestick.h"
#include "Weather.h"
#include <vector>

#include "CSVReader.h"

/**
 * @class MerkelMain
 * @brief Main class for managing the simulation
 */
class MerkelMain {
public:
  /** Constructor for MerkelMain */
  MerkelMain();
  /** Initializes and starts the simulation */
  void init();

private:
  /** Displays the main menu options */
  void printMenu();
  /** Shows help information */
  void printHelp();
  /** Displays current market statistics */
  void printMarketStats();
  /** Shows weather-related statistics */
  void printWeatherStats();
  /** Displays market predictions */
  void printPrediction();
  /** Advances simulation to next time period */
  void gotoNextTimeframe();
  /** Gets user input for menu selection
   * @return Selected menu option as integer */
  int getUserOption();
  /** Processes the user's menu selection
   * @param userOption The selected menu option */
  void processUserOption(int userOption);

  /** Displays filtered chart data */
  void printFilteredChart();

  /** Displays candlestick chart */
  void printCandlesticksChart();

  /** Prints individual candlestick data
   * @param candlestick The candlestick to display */
  void printCandlesticks(Candlestick &candlestick);

  /** Stores the current timestamp */
  std::string currentTime;

  /** Weather data object initialized with weather.csv file */
  Weather weather{"weather.csv"};
};
