#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <string>

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
  calculate_influence_map();
  //log_influence();

  return 0;
}














