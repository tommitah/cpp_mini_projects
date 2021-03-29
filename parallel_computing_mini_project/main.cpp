#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

constexpr auto COLS = 16;
constexpr auto ROWS = 16;

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

auto influence_in_tile(double unit_strength, double distance) {
  return unit_strength / (1 + distance);
}

auto calculate_influence_map() {
  for(int i = 0; i < COLS; i++) {
    for(int j = 0; i < ROWS; j++) {
      // foreach for map units
      for(auto& cols: map) {
        int k = 0;
        for(auto& rows: cols) {
          int h = 0;
          if(rows != 0) {
            influence_map[i][j] += influence_in_tile(rows, distance(k, h, i, j));
            std::cout << influence_map[i][j];
          }
          h++;
        }
        std::cout << std::endl;
        k++;
      }
    }
  }
}


/**
 * */
auto populate_map() {
  // AI units, amt: 7
  map[1][13] = 4;
  map[3][11] = 2;
  map[4][14] = 2;
  map[5][11] = 1;
  map[6][10] = 1;
  map[8][13] = 2;
  map[9][14] = 3;

  // player units, amt: 5
  map[2][2] = -2;
  map[10][4] = -2;
  map[12][9] = -2;
  map[14][7] = -2;
  map[15][12] = -2;
}

auto log_units() {
  for(int i = 0; i < COLS; i++) {
    for(int j = 0; j < ROWS; j++) {
      std::cout << map[i][j];
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

  return 0;
}














