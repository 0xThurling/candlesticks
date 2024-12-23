/**
 * Author: Jacques Thurling
 * Date: 2024-23-12
 * Notes: Used the main MerkelMain class from the initial program given
 * This is then used as the baseline to update the class to allow the
 * use of the new weather statistical functions and print methods
*/

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


  /**
   * =================================================
   * Code written by Jacques Thurling
   * =================================================
  */

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

  /**
   * ===================================================
   *  End of written code section
   * ===================================================
  */

};


