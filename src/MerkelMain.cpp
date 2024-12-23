/**
 * Author: Jacques Thurling
 * Date: 2024-23-12
 * Notes: Used the main MerkelMain class from the initial program given
 * This is then used as the baseline to update the class to allow the
 * use of the new weather statistical functions and print methods
*/

#include "MerkelMain.h"
#include "Candlestick.h"
#include "ChartRenderer.h"
#include "Prediction.h"
#include "Weather.h"
#include "WeatherEntry.h"
#include <exception>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

/**
 * MerkelMain.cpp
 * Main application class for a weather analysis and prediction system.
 * Handles user interaction and data visualization for weather patterns across
 * Europe.
 */
MerkelMain::MerkelMain() {}

/**
 * Main program loop that initializes the application and processes user
 * commands
 */
void MerkelMain::init() {
  // Variable to store user's menu selection
  int input;

  // Set the initial time to the earliest available time in weather data
  currentTime = weather.getEarliestTime();

  // Main program loop
  while (true) {
    // Display the menu options to the user
    printMenu();
    // Get the user's selected option
    input = getUserOption();
    // Process the user's selection
    processUserOption(input);
  }
}

/**
 * Displays the main menu options to the user
 */
void MerkelMain::printMenu() {
  // 1 print help
  std::cout << "1: Print help " << std::endl;
  // 2 print Weather for region
  std::cout << "2: Print Weather data for region" << std::endl;
  // 3 print Candlestick Chart for region and year
  std::cout << "3: Print Candlestick chart for region and year" << std::endl;
  // 4 print Graph Chart for date range and region
  std::cout << "4: Print Graph for date range and region" << std::endl;
  // 5 get prediction and then Print the prediction in a graph
  std::cout << "5: Predict future temperatures" << std::endl;
  // 6 continue
  std::cout << "6: Continue " << std::endl;

  std::cout << "============== " << std::endl;
}

/** Displays help information about the program's purpose */
void MerkelMain::printHelp() {
  std::cout
      << "Help - Analyse weather patterns in different regions of Europe. "
      << std::endl;
}

/**
 * ==============================================
 * Code written by Jacques Thurling
 * ==============================================
*/

/**
 * Prints weather statistics for a specified region showing open, high, low and
 * closing temperatures Format: region code (e.g. FR for France)
 */
void MerkelMain::printWeatherStats() {
  // Prompt user for region input
  std::cout << "Enter the region (FR): " << std::endl;
  std::string input;
  std::getline(std::cin, input);

  // Split input into tokens (though only one token expected)
  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

  // Container for weather entries
  std::vector<WeatherEntry> temp;

  try {
    // Convert input string to region enum type
    WeatherEntryType region = WeatherEntry::mapFromInputToRegion(tokens[0]);

    // Start from 1980 as base year
    int year = 1980;

    // Print header for data table
    std::cout << "Date                   Open       High      Low      Closing"
              << std::endl;
    // Set decimal precision for temperature values
    std::cout << std::fixed << std::setprecision(3);

    // Process data year by year until no more data is available
    do {
      // Get weather entries for current year and region
      temp = std::get<std::vector<WeatherEntry>>(
          weather.getWeatherEntries(region, std::to_string(year)));

      // Exit loop if no data found for current year
      if (temp.size() == 0) {
        break;
      }

      // Calculate temperature statistics for the year
      double lowestTemp = Weather::getLowestTemp(temp);
      double highestTemp = Weather::getHighestTemp(temp);
      double closingTemp = Weather::getClosingTemp(temp);
      double openingTemp = Weather::getOpeningTemp(temp);

      // Print statistics for current year
      std::cout << temp.begin()->timeframe << "   " << openingTemp << "      "
                << highestTemp << "   " << lowestTemp << "   " << closingTemp
                << std::endl;

      // Move to next year
      year++;
    } while (temp.size() > 0);

  } catch (const std::exception &e) {
    // Handle any errors during data processing
    std::cout << "MerkelMain::printWeatherStats error when mapping and "
                 "retrieving entries"
              << std::endl;
  }
}

/**
 * Generates and displays a candlestick chart for temperature data
 * Format: region,year (e.g. FR,1990)
 */
void MerkelMain::printCandlesticksChart() {
  // Prompt user for input in format: region,year
  std::cout << "Enter the region and year (FR,1990): " << std::endl;
  std::string input;
  std::getline(std::cin, input);

  // Split input string into tokens using comma as delimiter
  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

  // Container for monthly temperature entries
  std::vector<std::vector<WeatherEntry>> monthly_entries;

  try {
    // Convert region string to enum type
    WeatherEntryType region = WeatherEntry::mapFromInputToRegion(tokens[0]);

    // Retrieve monthly weather data for specified region and year
    monthly_entries = std::get<std::vector<std::vector<WeatherEntry>>>(
        weather.getWeatherEntries(region, tokens[1],
                                  WeatherFilterOptions::monthly));

  } catch (const std::exception &e) {
    // Handle any errors during data retrieval
    std::cout << "MerkelMain::printWeatherStats error when mapping and "
                 "retrieving entries"
              << std::endl;
    throw e;
  }

  // Container for candlestick data
  std::vector<Candlestick> candlesticks;

  // Process each month's data into candlestick format
  for (int i = 0; i < monthly_entries.size(); i++) {
    // Calculate temperature metrics for the month
    double lowestTemp = Weather::getLowestTemp(monthly_entries[i]);
    double highestTemp = Weather::getHighestTemp(monthly_entries[i]);
    double closingTemp = monthly_entries[i].end()->temp;
    double openingTemp = monthly_entries[i].begin()->temp;

    // Create candlestick object with temperature data
    Candlestick candlestick{openingTemp, closingTemp, highestTemp, lowestTemp};

    // Add to collection
    candlesticks.push_back(candlestick);
  }

  // Display the candlestick chart
  Candlestick::printCandleStickChart(candlesticks);
}

/**
 * Makes temperature predictions using historical data and displays forecast
 * Uses a prediction model to estimate next 5 temperature values
 */
void MerkelMain::printPrediction() {
  // Prompt user for region input
  std::cout << "Enter the region (FR): " << std::endl;
  std::string input;
  std::getline(std::cin, input);

  // Parse input into tokens
  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

  // Initialize containers for weather data and candlestick patterns
  std::vector<WeatherEntry> temp;
  std::vector<Candlestick> data;

  // Start year for historical data collection
  int year = 1980;

  try {
    // Convert input string to region enum
    WeatherEntryType region = WeatherEntry::mapFromInputToRegion(tokens[0]);

    std::cout << "Making Predictions" << std::endl;

    // Set decimal precision for temperature output
    std::cout << std::fixed << std::setprecision(3);

    // Collect historical temperature data year by year
    do {
      // Get weather entries for current year and region
      temp = std::get<std::vector<WeatherEntry>>(
          weather.getWeatherEntries(region, std::to_string(year)));

      // Break if no data available for current year
      if (temp.size() == 0) {
        break;
      }

      // Calculate temperature metrics for the year
      double lowestTemp = Weather::getLowestTemp(temp);
      double highestTemp = Weather::getHighestTemp(temp);
      double closingTemp = Weather::getClosingTemp(temp);
      double openingTemp = Weather::getOpeningTemp(temp);

      // Create candlestick object from temperature data
      Candlestick candle{openingTemp, closingTemp, highestTemp, lowestTemp};

      // Add to historical data collection
      data.push_back(candle);

      year++;
    } while (temp.size() > 0);

  } catch (const std::exception &e) {
    std::cout << "MerkelMain::printWeatherStats error when mapping and "
                 "retrieving entries"
              << std::endl;
  }

  // Create and train prediction model using historical data
  Prediction model{data};
  model.fit();

  // Generate 5-year temperature forecast
  std::vector<double> forecast = model.predict(5);
  std::cout << "Next 5 temps: " << std::endl;

  // Prepare data structure for visualization
  std::vector<std::vector<WeatherEntry>> chart;

  // Convert forecast data to WeatherEntry format
  for (int i = 0; i < forecast.size(); i++) {
    std::vector<WeatherEntry> predictions;

    // Create WeatherEntry for each predicted temperature
    WeatherEntry prediction{forecast[i],
                            std::to_string(year) + "-01-01T00:00:00Z",
                            WeatherEntry::mapFromInputToRegion(tokens[0])};

    predictions.push_back(prediction);
    chart.push_back(predictions);
  }

  // Display forecast as graph
  ChartRenderer::printGraph(chart);
}

/**
 * Advances the current timeframe to the next period
 */
void MerkelMain::gotoNextTimeframe() {
  // Inform user that timeframe is advancing
  std::cout << "Going to next time frame. " << std::endl;
  // Split current timestamp into tokens using '-' as delimiter
  std::vector<std::string> tokens = CSVReader::tokenise(currentTime, '-');

  // Update current time to next available timeframe in weather data
  // tokens[0] contains the current timestamp
  currentTime = weather.goToNextTimeFrame(tokens[0]);
}

/**
 * Gets and validates user input for menu options (1-6)
 * @return int Selected menu option
 */
int MerkelMain::getUserOption() {
  // Initialize user's selection
  int userOption = 0;
  std::string line;

  // Prompt user for input
  std::cout << "Type in 1-6" << std::endl;
  // Get entire line of input from user
  std::getline(std::cin, line);
  try {
    // Convert string input to integer
    userOption = std::stoi(line);
  } catch (const std::exception &e) {
    // If conversion fails, userOption remains 0
    // This handles invalid inputs like letters or special characters
  }

  // Echo user's selection
  std::cout << "You chose: " << userOption << std::endl;
  return userOption;
}

/**
 * Displays temperature data as a graph for a specified date range
 * Format: region,start_year,end_year (e.g. FR,1990,2001)
 */
void MerkelMain::printFilteredChart() {
  // Prompt user for input
  std::cout << "Enter the region, start year and end year e.g. FR,1990,2001: "
            << std::endl;
  std::string input;
  std::getline(std::cin, input);

  // Split input string into tokens using comma as delimiter
  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

  try {
    // Calculate the year range
    int year_difference = std::stoi(tokens[2]) - std::stoi(tokens[1]);

    // Convert region string to enum type
    WeatherEntryType region = WeatherEntry::mapFromInputToRegion(tokens[0]);

    // Validate year range is positive
    if (year_difference < 1) {
      std::cout << "Please choose valid years" << std::endl;
      return;
    }

    // Container for weather data across multiple years
    std::vector<std::vector<WeatherEntry>> weatherDataYearlyEntries;

    // Collect weather data for each year in the range
    for (int i = 0; i <= year_difference; i++) {
      int year = std::stoi(tokens[1]) + i;

      // Get weather entries for current year and region
      std::vector<WeatherEntry> temp = std::get<std::vector<WeatherEntry>>(
          weather.getWeatherEntries(region, std::to_string(year)));
      weatherDataYearlyEntries.push_back(temp);
    }

    // Render the graph using collected data
    ChartRenderer::printGraph(weatherDataYearlyEntries);

  } catch (const std::exception &e) {
    // Handle any errors during processing
    std::cout << "printFilteredChart - there has been an error" << std::endl;
  }
}

/**
 * Processes the user's menu selection and calls appropriate functions
 * @param userOption Selected menu option (1-6)
 */
void MerkelMain::processUserOption(int userOption) {
  if (userOption == 0) // bad input
  {
    std::cout << "Invalid choice. Choose 1-6" << std::endl;
  }

  // Display help menu and available commands
  if (userOption == 1) {
    printHelp();
  }

  // Show statistical analysis of weather data
  if (userOption == 2) {
    printWeatherStats();
  }

  // Display temperature data as candlestick chart
  if (userOption == 3) {
    printCandlesticksChart();
  }

  // Show filtered temperature data visualization
  if (userOption == 4) {
    printFilteredChart();
  }

  // Calculate and display weather predictions
  if (userOption == 5) {
    printPrediction();
  }

  // Advance to next time period in the dataset
  if (userOption == 6) {
    gotoNextTimeframe();
  }
}
/**
 * ===================================================
 *  End of written code section
 * ===================================================
*/


