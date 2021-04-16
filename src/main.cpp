#include <iostream>
#include <cstdlib>
#include <ctime>

#include "utils.hpp"
#include "synchronizer.hpp"


#define MAX_SIZE 100
#define MIN_VALUE 1
#define MAX_VALUE 9
#define MAX_FOR_REMOVING 15

template <class T>
static void fill(std::vector<T> &v, std::map<int, T> &m) {
  int v_size = random_value(MAX_SIZE, 1);
  int m_size = random_value(MAX_SIZE, 1);
  int i;

  v.reserve(v_size);
  for (i = 0; i < v_size && i < m_size ; ++i) {
    v.emplace_back(random_value(MAX_VALUE, MIN_VALUE));
    m[i] = random_value(MAX_VALUE, MIN_VALUE);
  }
  while (i < v_size) {
    v.emplace_back(random_value(MAX_VALUE, MIN_VALUE));
    i++;
  }
  while (i < m_size) {
    m[i] = random_value(MAX_VALUE, MIN_VALUE);
    ++i;
  }
}

template <class T>
static void remove(std::vector<T> &v, std::map<int, T> &m) {
  int v_del = random_value(MAX_FOR_REMOVING);
  int m_del = random_value(MAX_FOR_REMOVING);
  int i;

  if (v_del >= v.size()) {
    v.clear();
  }
  if (m_del >= m.size()) {
    m.clear();
  }
  for (i = 0; !v.empty() && i < v_del && !m.empty() && i < m_del; ++i) {
    vector_random_remove_one<T>(v);
    map_random_remove_one<T>(m);
  }
  while (!v.empty() && i < v_del) {
    vector_random_remove_one<T>(v);
    ++i;
  }
  while (!m.empty() && i < m_del) {
    map_random_remove_one<T>(m);
    ++i;
  }
}

int main() {
  srand(time(nullptr));

  std::vector<int>   vector;
  std::map<int, int> map;

  fill<int>(vector, map);    // fill containers random values from 1 to 9
  remove<int>(vector, map);  // remove random values no more than 15

  std::cout <<  "\x1b[32mBefore synchronize ==========\n\x1b[0m";
  visualize_vector<int>(vector);
  visualize_map<int>(map);
  std::cout << "\x1b[32m=============================\n\x1b[0m" << std::endl;

  synchronize<int>(vector, map);  // synchronize containers

  std::cout << "\x1b[32mAfter synchronize ===========\n\x1b[0m";
  visualize_vector<int>(vector);
  visualize_map<int>(map);
  std::cout << "\x1b[32m=============================\n\x1b[0m" << std::endl;
  return 0;
}
