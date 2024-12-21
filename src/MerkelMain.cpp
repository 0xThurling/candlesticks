#include "MerkelMain.h"
#include <exception>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>
#include "Candlestick.h"
#include "ChartRenderer.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
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
    std::cout << "2: Print Weather for region" << std::endl;
    // 3 print chart for filtered data
    std::cout << "3: Print Graph for date range and region" << std::endl;
 

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
  std::cout << "Enter the region and year (FR,1990): " << std::endl;
  std::string input;
  std::getline(std::cin, input);

  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

  std::vector<WeatherEntry> currentYearEntries;
  std::vector<WeatherEntry> previousYearEntries;

  try {
    WeatherEntryType region = WeatherEntry::mapFromInputToRegion(tokens[0]);

    int previousYear = std::stoi(tokens[1]) - 1;

    currentYearEntries  = weather.getWeatherEntries(region, tokens[1]);
    previousYearEntries = weather.getWeatherEntries(region, std::to_string(previousYear));

  } catch (const std::exception& e) {
    std::cout << "MerkelMain::printWeatherStats error when mapping and retrieving entries" << std::endl;
  }

  double lowestTemp = Weather::getLowestTemp(currentYearEntries);
  double highestTemp = Weather::getHighestTemp(currentYearEntries);
  double closingTemp = Weather::getClosingTemp(currentYearEntries);
  double openingTemp = Weather::getOpeningTemp(previousYearEntries);

  std::vector<Candlestick> candlesticks;
  Candlestick candlestick{openingTemp, closingTemp, highestTemp, lowestTemp};

  candlesticks.push_back(candlestick);

  Candlestick::printCandleStickChart(candlesticks);
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

      std::vector<WeatherEntry> temp = weather.getWeatherEntries(region ,std::to_string(year));
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
        printFilteredChart();
    }
    if (userOption == 6) 
    {
        gotoNextTimeframe();
    }       
}
