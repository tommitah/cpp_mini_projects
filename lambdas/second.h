#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

inline void print_points(std::vector<int>& hit_points) {
  std::cout << std::endl;
  for(auto points : hit_points) std::cout << points << std::endl;
}

inline auto operation_separate(int& hit_points) {
  hit_points >= 100 ? hit_points -= 100 : hit_points = 0;
}

auto operation_named_lambda = [](int& n) {
  n >= 100 ? n -= 100 : n = 0;
};



inline void lambdas_func_objects() {
  std::vector<int> enemy_hit_points { 999, 256, 666, 1337, 13131 };

  //separate
  std::for_each(enemy_hit_points.begin(), enemy_hit_points.end(), operation_separate);
  print_points(enemy_hit_points);

  //lambda
  std::for_each(enemy_hit_points.begin(), enemy_hit_points.end(), [](int& n) {
    n >= 100 ? n -= 100 : n = 0;
  });
  print_points(enemy_hit_points);

  //named lambda
  std::for_each(enemy_hit_points.begin(), enemy_hit_points.end(), operation_named_lambda);
  print_points(enemy_hit_points);

}
