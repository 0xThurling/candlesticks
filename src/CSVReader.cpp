#include "CSVReader.h"
#include "Weather.h"
#include "WeatherEntry.h"
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


CSVReader::CSVReader()
{

}

std::vector<WeatherEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<WeatherEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open())
    {
        while(std::getline(csvFile, line))
        {
            try {
              std::vector<WeatherEntry> woe = stringsToWE(tokenise(line, ','));
              for (const WeatherEntry& entry : woe) {
                entries.push_back(entry); 
              }
            }catch(const std::exception& e)
            {
                std::cout << "CSVReader::readCSV bad data"  << std::endl;
            }
        }// end of while
    }    

    std::cout << "CSVReader::readCSV read " << entries.size() << " entries"  << std::endl;
    return entries; 
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
   std::vector<std::string> tokens;
   signed int start, end;
   std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do{
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
    start = end + 1;
    }while(end > 0);

   return tokens; 
}

std::vector<WeatherEntry> CSVReader::stringsToWE(std::vector<std::string> strings){
  std::vector<WeatherEntry> entries;

  for (int i = 1; i < strings.size(); i++) {
    try {
      WeatherEntryType region = WeatherEntry::mapFromTokenToRegion(i);
      double temperature = std::stod(strings[i]);
      std::string timeframe = strings[0];

      WeatherEntry entry{temperature, timeframe, region};
      entries.push_back(entry);
    } catch (const std::exception& e) {
      std::cout << "CSVReader::stringsToW - error processing index " << i << " on timeframe: " << strings[0];
      continue;
    }
  }

  return entries;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;

    if (tokens.size() != 5) // bad
    {
        std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    // we have 5 tokens
    try {
         price = std::stod(tokens[3]);
         amount = std::stod(tokens[4]);
    }catch(const std::exception& e){
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[3]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[4]<< std::endl; 
        throw;        
    }

    OrderBookEntry obe{price, 
                        amount, 
                        tokens[0],
                        tokens[1], 
                        OrderBookEntry::stringToOrderBookType(tokens[2])};

    return obe; 
}


OrderBookEntry CSVReader::stringsToOBE(std::string priceString, 
                                    std::string amountString, 
                                    std::string timestamp, 
                                    std::string product, 
                                    OrderBookType orderType)
{
    double price, amount;
    try {
         price = std::stod(priceString);
         amount = std::stod(amountString);
    }catch(const std::exception& e){
        std::cout << "CSVReader::stringsToOBE Bad float! " << priceString<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << amountString<< std::endl; 
        throw;        
    }
    OrderBookEntry obe{price, 
                    amount, 
                    timestamp,
                    product, 
                    orderType};
                
    return obe;
}
     
