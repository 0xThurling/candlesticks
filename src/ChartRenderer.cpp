#include "ChartRenderer.h"
#include "Weather.h"
#include "WeatherEntry.h"
#include <cmath>
#include <iostream>
#include <iterator>
#include <string>
#include <strings.h>
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

  std::cout << data_to_render.size() << std::endl;

  for (int i = 0; i < data_to_render.size();i++) {
    std::cout << data_to_render[i].temp << std::endl;
  }

  std::cout << std::endl;

  int temp = 50;

  for (int i = 0; i < height; i++) {
    temp = mapYCoordFromIndex((double)i);
    for (int j = 0; j < width;j++) {
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
      } else {
        WeatherEntry start = data_to_render[floor(j/10)];
        WeatherEntry end = data_to_render[floor(j/10) + 1];

        // Skip the iterations once we hit the end
        if (floor(j/10)+1 >= data_to_render.size()) {
          continue;
        }
      }
    }
    std::cout << std::endl;
  }
}


double ChartRenderer::mapYCoordFromIndex(double index){
  return -0.56 * index + 13.0;
}
