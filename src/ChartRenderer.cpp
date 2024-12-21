#include "ChartRenderer.h"
#include "Weather.h"
#include "WeatherEntry.h"
#include <iostream>
#include <string>
#include <vector>

ChartRenderer::ChartRenderer(){}

void ChartRenderer::printGraph(std::vector<std::vector<WeatherEntry>> yearly_entries){
  std::vector<WeatherEntry> data_to_render;

  // Use more memory for rendering - keep data separate
  for (std::vector<WeatherEntry> entries : yearly_entries) {
    std::string time = entries.begin()->timeframe;

    double mean_temp = Weather::getClosingTemp(entries);
  
    WeatherEntry new_entry {
      mean_temp,
      time,
      entries.begin()->region
    };

    data_to_render.push_back(new_entry);
  }

  unsigned int height = 25;
  unsigned int width = 90;

  std::cout << std::endl;

  int temp = 50;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < height; j++) {
      if (j == 0 && i == height - 1) {
        std::cout << "    └";
      } else if (j == 0) {
        if ((i % 2) == 0) {
          // Prepare the y-axis
          if(temp < -10) {
            std::cout << temp << " ┤";
          } else if (temp < 10 && temp > -1) {
            std::cout << "  " << temp << " ┤";
          } else if (temp < -1 && temp > -10) {
            std::cout << " " << temp << " ┤";
          } else {
            std::cout << " " << temp << " ┤";
          }
        } else {
          std::cout << "    │";
        }
      } else if (i == height - 1) {
        // Populate the x-axis
        if (j % 10 == 0) {
          std::cout << "┬";
        } else {
          std::cout << "─";
        }
      } 
    }
  }
}
