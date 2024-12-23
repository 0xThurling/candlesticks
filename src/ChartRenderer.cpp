#include "ChartRenderer.h"
#include "Weather.h"
#include "WeatherEntry.h"
#include <cmath>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <strings.h>
#include <vector>

// Default constructor
ChartRenderer::ChartRenderer() {}

// Prints a line graph visualization of weather data
void ChartRenderer::printGraph(
    std::vector<std::vector<WeatherEntry>> yearly_entries) {
  std::vector<WeatherEntry> data_to_render;

  // Use more memory for rendering - keep data separate
  for (std::vector<WeatherEntry> entries : yearly_entries) {
    std::string time = entries.begin()->timeframe;

    // Process and prepare data for rendering
    // Extract mean temperatures for each timeframe
    double mean_temp = Weather::getClosingTemp(entries);

    // Create new entry with processed data
    WeatherEntry new_entry{mean_temp, time, entries.begin()->region};

    data_to_render.push_back(new_entry);
  }

  // Set chart dimensions
  unsigned int height = 25;
  unsigned int width = 90;

  std::cout << data_to_render.size() << std::endl;

  // Debug output - print data size and temperatures
  for (int i = 0; i < data_to_render.size(); i++) {
    std::cout << data_to_render[i].temp << std::endl;
  }

  std::cout << std::endl;

  double temp = 50;

  // Iterate through each row of the chart
  for (int i = 0; i < height; i++) {

    // Calculate temperature for current row
    temp = round(mapYCoordFromIndex((double)i) * 10.0) / 10.0;
    std::cout << std::fixed << std::setprecision(1);

    // Iterate through each column
    for (int j = 0; j < width; j++) {
      if (j == 0 && i == height - 1) {
        std::cout << "      └";
      } else if (j == 0) {
        if ((i % 2) == 0) {
          // Prepare the y-axis
          if (temp < -10) {
            std::cout << temp << " ┤";
          } else if (temp < 10 && temp > -1) {
            std::cout << "  " << temp << " ┤";
          } else if (temp < -1 && temp > -10) {
            std::cout << " " << temp << " ┤";
          } else {
            std::cout << " " << temp << " ┤";
          }
        } else {
          std::cout << "      │";
        }
      } else if (i == height - 1) {
        // Populate the x-axis
        // Draw x-axis with tick marks
        if (j % 10 == 0) {
          std::cout << "┬";
        } else {
          std::cout << "─";
        }
      } else {
        // Plot data points and connecting lines
        WeatherEntry start = data_to_render[floor(j / 10)];
        WeatherEntry end = data_to_render[floor(j / 10) + 1];

        if (j % 10 == 0) {
          // Draw data points
          if (start.temp > mapYCoordFromIndex(i + 1) && start.temp < temp) {
            std::cout << "*";
          } else {
            std::cout << " ";
          }
        } else {
          // Draw connecting lines between data points
          double linSpace = linearSpace(start.temp, end.temp, j % 10);

          if (linSpace > mapYCoordFromIndex(i + 1) && linSpace < temp) {
            std::cout << "*";
          } else {
            std::cout << " ";
          }
        }
      }
    }
    std::cout << std::endl;
  }
}

// Maps y-coordinate index to temperature value
// Creates the temperature scale on the y-axis
double ChartRenderer::mapYCoordFromIndex(double index) {
  return -0.56 * index + 13.0;
}

// Calculates intermediate points for line drawing between two temperatures
// Uses linear interpolation
double ChartRenderer::linearSpace(double y1, double y2, double i) {
  return y1 + (i / (10 - 1)) * (y2 - y1);
}
