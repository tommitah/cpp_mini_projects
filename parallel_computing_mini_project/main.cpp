#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <execution>
#include <future>

constexpr auto COLS = 300;
constexpr auto ROWS = 300;

/**
 * Military unit strengths (positive = AI unit,
 * negative = player unit, 0 = empty)
 * */
double map[COLS][ROWS];

/**
 * Influence map.
 * */
double influence_map[COLS][ROWS];

std::vector<std::array<double, 300>> inf_map_rows = {};

/**
 * Calculates distance between (c0, r0) and (c1, r1).
 * */
inline double distance(int c0, int r0, int c1, int r1) {
  return sqrt((r0 - r1) * (r0 - r1) + (c0 - c1) * (c0 - c1));
}

auto time_elapsed(const std::chrono::steady_clock::time_point& start,
    const std::chrono::steady_clock::time_point& end) {
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cout << "time: " << elapsed_seconds.count() << std::endl;
}

auto calculate_influence_map() {
  auto start = std::chrono::steady_clock::now();
  for(int i = 0; i < COLS; i++) {
    for(int j = 0; j < ROWS; j++) {
      influence_map[i][j] = 0;
      for(int k = 0; k < COLS; k++) {
        for(int h = 0; h < ROWS; h++) {
          influence_map[i][j] += (map[k][h] / 
              (1 + distance(i, j, k, h)));
        }
      }
    }
  }
  auto end = std::chrono::steady_clock::now();
  time_elapsed(start, end);
}

auto inf_in_row = [](auto arr) { 
  for(int i = 0; i < COLS; i++) {
    for(int j = 0; j < ROWS; j++) {
      arr[i] = 0;
      for(int x = 0; x < COLS; x++) {
        for(int y = 0; y < ROWS; y++) {
          arr[i] += (map[x][y] / (1 + distance(i, j, x, y)));
        }
      }
    }
  }
};


//auto calc_inf_async() {
  //auto start = std::chrono::steady_clock::now();

  //std::future<std::vector<std::array<double, 300>>> inf_map = 
    //std::async(std::launch::deferred, inf_in_row,
        //inf_map_rows.begin(), inf_map_rows.end());

  //auto end = std::chrono::steady_clock::now();
  //time_elapsed(start, end);
//}

auto calc_inf_for_each() {
  auto start = std::chrono::steady_clock::now();

  std::for_each(std::execution::par_unseq, inf_map_rows.begin(), 
      inf_map_rows.end(), inf_in_row);

  auto end = std::chrono::steady_clock::now();
  time_elapsed(start, end);
}

/**
 * */
auto populate_map() {
  // AI units, amt: 7
  map[19][244] = 80;
  map[56][206] = 40;
  map[75][263] = 40;
  map[94][206] = 20;
  map[113][188] = 20;
  map[150][244] = 40;
  map[169][263] = 60;

  // player units, amt: 5
  map[38][38] = -40;
  map[187][7] = -40;
  map[225][168] = -40;
  map[263][131] = -40;
  map[281][225] = -40;
}

auto log_units() {
  for(int i = 0; i < COLS; i++) {
    for(int j = 0; j < ROWS; j++) {
      std::cout << map[i][j];
    }
    std::cout << std::endl;
  }
}

auto log_influence() {
  for(int i = 0; i < COLS; i++) {
    for(int j = 0; j < ROWS; j++) {
      std::cout << influence_map[i][j];
    }
    std::cout << std::endl;
  }
}

// Copy a row to std::array to be stored int the vector.
auto set_map_vector() {
  for(int i = 0; i < COLS; i++) {
    std::array<double, 300> arr;
    for(int j = 0; j < ROWS; j++) 
      arr[i] = map[i][j];
    inf_map_rows.push_back(arr);
  }
  std::cout << "Vector size: " << inf_map_rows.size();
} 


int main() {
  /**
   * TODO
   *
   * Calculate influence_map values from map values.
   * */

  /**
   * Seed data.
   * */
  populate_map();
  //log_units();
  set_map_vector();
  calc_inf_for_each();
  //calculate_influence_map();
  //log_influence();

  return 0;
}














