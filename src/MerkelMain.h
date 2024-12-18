#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "Weather.h"


class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        void init();
    private: 
        void printMenu();
        void printHelp();
        void printMarketStats();
        void printWeatherStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int getUserOption();
        void processUserOption(int userOption);

        std::string currentTime;

        Wallet wallet;

        Weather weather{"weather.csv"};
};
