#include "MerkelMain.h"
#include <exception>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>
#include "Candlestick.h"
#include "ChartRenderer.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "Prediction.h"
#include "Weather.h"
#include "WeatherEntry.h"

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    int input;

    currentTime = weather.getEarliestTime();
    
    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}


void MerkelMain::printMenu()
{
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

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats() {}


void MerkelMain::printWeatherStats() {
  std::cout << "Enter the region (FR): " << std::endl;
  std::string input;
  std::getline(std::cin, input);

  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

  std::vector<WeatherEntry> temp;
    
  try {
    WeatherEntryType region = WeatherEntry::mapFromInputToRegion(tokens[0]);

    int year = 1980;
    
    
    std::cout << "Date                   Open       High      Low      Closing" << std::endl;
    
    std::cout << std::fixed << std::setprecision(3);

    do {
      temp = std::get<std::vector<WeatherEntry>>(weather.getWeatherEntries(region, std::to_string(year)));

      if (temp.size() == 0) {
        break;
      }

      double lowestTemp = Weather::getLowestTemp(temp);
      double highestTemp = Weather::getHighestTemp(temp);
      double closingTemp = Weather::getClosingTemp(temp);
      double openingTemp = Weather::getOpeningTemp(temp);

      std::cout << temp.begin()->timeframe << "   " << openingTemp << "      " << highestTemp << "   " << lowestTemp << "   " << closingTemp << std::endl;

      year++;
    } while (temp.size() > 0);

  } catch (const std::exception& e) {
    std::cout << "MerkelMain::printWeatherStats error when mapping and retrieving entries" << std::endl;
  }

}

void MerkelMain::printCandlesticksChart() {
  std::cout << "Enter the region and year (FR,1990): " << std::endl;
  std::string input;
  std::getline(std::cin, input);

  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

  std::vector<std::vector<WeatherEntry>> monthly_entries;

  try {
    WeatherEntryType region = WeatherEntry::mapFromInputToRegion(tokens[0]);

    monthly_entries = std::get<std::vector<std::vector<WeatherEntry>>>(
        weather.getWeatherEntries(region, tokens[1], WeatherFilterOptions::monthly));

  } catch (const std::exception& e) {
    std::cout << "MerkelMain::printWeatherStats error when mapping and retrieving entries" << std::endl;
    throw e;
  }

  std::vector<Candlestick> candlesticks;

  for (int i = 0; i < monthly_entries.size(); i++) {
    double lowestTemp = Weather::getLowestTemp(monthly_entries[i]);
    double highestTemp = Weather::getHighestTemp(monthly_entries[i]);
    double closingTemp = monthly_entries[i].end()->temp;
    double openingTemp = monthly_entries[i].begin()->temp;

    Candlestick candlestick{openingTemp, closingTemp, highestTemp, lowestTemp};

    candlesticks.push_back(candlestick);
  }

  Candlestick::printCandleStickChart(candlesticks);
}

void MerkelMain::printPrediction(){
  std::cout << "Enter the region (FR): " << std::endl;
  std::string input;
  std::getline(std::cin, input);

  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

  std::vector<WeatherEntry> temp;
  std::vector<Candlestick> data;
  
  int year = 1980;
  
  try {
    WeatherEntryType region = WeatherEntry::mapFromInputToRegion(tokens[0]);

    std::cout << "Making Predictions" << std::endl;
    
    std::cout << std::fixed << std::setprecision(3);

    do {
      temp = std::get<std::vector<WeatherEntry>>(weather.getWeatherEntries(region, std::to_string(year)));

      if (temp.size() == 0) {
        break;
      }

      double lowestTemp = Weather::getLowestTemp(temp);
      double highestTemp = Weather::getHighestTemp(temp);
      double closingTemp = Weather::getClosingTemp(temp);
      double openingTemp = Weather::getOpeningTemp(temp);

      Candlestick candle {openingTemp, closingTemp, highestTemp, lowestTemp};

      data.push_back(candle);

      year++;
    } while (temp.size() > 0);

  } catch (const std::exception& e) {
    std::cout << "MerkelMain::printWeatherStats error when mapping and retrieving entries" << std::endl;
  }

  Prediction model {data};
  model.fit();

  std::vector<double> forecast = model.predict(5);
  std::cout << "Next 5 temps: " << std::endl;


  std::vector<std::vector<WeatherEntry>> chart;

  for (int i = 0; i < forecast.size(); i++) {
    std::vector<WeatherEntry> predictions;

    WeatherEntry prediction {
        forecast[i],
        std::to_string(year) + "-01-01T00:00:00Z",
        WeatherEntry::mapFromInputToRegion(tokens[0])
    };

    predictions.push_back(prediction);
    chart.push_back(predictions);
  }

  ChartRenderer::printGraph(chart);
}

void MerkelMain::enterAsk()
{
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::ask 
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
        }   
    }
}

void MerkelMain::enterBid()
{
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::bid 
            );
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterBid Bad input " << std::endl;
        }   
    }
}

void MerkelMain::printWallet()
{}
        
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    std::vector<std::string> tokens = CSVReader::tokenise(currentTime, '-');

    currentTime = weather.goToNextTimeFrame(tokens[0]);
}
 
int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-6" << std::endl;
    std::getline(std::cin, line);
    try{
        userOption = std::stoi(line);
    }catch(const std::exception& e)
    {
        // 
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::printFilteredChart(){
  std::cout << "Enter the region, start year and end year e.g. FR,1990,2001: " << std::endl;
  std::string input;
  std::getline(std::cin, input);

  std::vector<std::string> tokens = CSVReader::tokenise(input,',');

  try {
    int year_difference = std::stoi(tokens[2]) - std::stoi(tokens[1]);

    WeatherEntryType region = WeatherEntry::mapFromInputToRegion(tokens[0]);

    if (year_difference < 1) {
      std::cout << "Please choose valid years" << std::endl;
      return;
    }

    std::vector<std::vector<WeatherEntry>> weatherDataYearlyEntries;

    for (int i = 0; i <= year_difference; i++) {
      int year = std::stoi(tokens[1]) + i;

      std::vector<WeatherEntry> temp = std::get<std::vector<WeatherEntry>>(
          weather.getWeatherEntries(region, std::to_string(year)));
      weatherDataYearlyEntries.push_back(temp);
    }

    ChartRenderer::printGraph(weatherDataYearlyEntries);

  } catch (const std::exception& e) {
    std::cout << "printFilteredChart - there has been an error" << std::endl;
  }
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1) 
    {
        printHelp();
    }
    if (userOption == 2) 
    {
        printWeatherStats();
    }
    if (userOption == 3) 
    {
        printCandlesticksChart();
    }
    if (userOption == 4) 
    {
        printFilteredChart();
    }
    if (userOption == 5) 
    {
        printPrediction();
    }
    if (userOption == 6) 
    {
        gotoNextTimeframe();
    }       
}
