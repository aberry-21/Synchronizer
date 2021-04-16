//
// Created by Gueren Drive on 4/16/21.
//

#include <cstdlib>

int  random_value(int max_value = RAND_MAX, int min_value = 0) {
  int value = rand() % max_value + 1;

  while (value < min_value) {
    value = rand() % max_value + 1;
  }
  return value;
}
