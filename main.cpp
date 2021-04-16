#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
#include <algorithm>


#define MAX_SIZE 100
#define MIN_VALUE 1
#define MAX_VALUE 9
#define MAX_FOR_REMOVING 15

static int  random_value(int max_value = RAND_MAX, int min_value = 0) {
  int value = rand() % max_value + 1;

  while (value < min_value) {
    value = rand() % max_value + 1;
  }
  return value;
}

template <class T>
static void visualize_vector(const std::vector<T> &v) {
  std::cout << "vector:\n";
  for (typename std::vector<T>::size_type i = 0; i < v.size(); ++i) {
    if (i != 0 && i % 32 == 0) {
      std::cout << "\n";
    }
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}

template <class T>
static void visualize_map(const std::map<int, T> &m) {
  auto   first(m.begin());
  auto   last(m.end());
  size_t i = 0;

  std::cout << "map:" << std::endl;
  while (first != last) {
    if (i != 0 && i % 32 == 0) {
      std::cout << "\n";
    }
    std::cout << first->second << " ";
    ++first;
    ++i;
  }
  std::cout << std::endl;
}

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
static void vector_random_remove_one(std::vector<T> &v) {
  v.erase(v.begin() + random_value(v.size() - 1));
}

template <class T>
static void map_random_remove_one(std::map<int, T> &m) {
  typename std::map<int, T>::iterator m_it;
  int index;

  if (m.empty()) {
    return;
  }
  index = random_value(m.size() - 1);
  m_it = m.begin();
  while (index) {
    ++m_it;
    --index;
  }
  m.erase(m_it);
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

template <class T>
static void map_to_vector(std::vector<T> &v, const std::map<int, T> &m) {
  auto first(m.begin());
  auto last(m.end());

  v.clear();
  v.reserve(m.size());
  while (first != last) {
    v.emplace_back(first->second);
    ++first;
  }
}

template <class T>
static void vector_to_map(std::map<int, T> &m, std::vector<T> &v) {
  m.clear();
  for (int i = 0; i < v.size(); ++i) {
    m[i] = v[i];
  }
}

template <class T>
static void synchronize(std::vector<T> &v, std::map<int, T> &m) {
  if (v.empty() || m.empty()) {
    v.clear();
    m.clear();
    return;
  }
  std::vector<T> from_map;
  std::vector<T> intersection;

  map_to_vector<T>(from_map, m);
  std::sort(v.begin(), v.end());
  std::sort(from_map.begin(), from_map.end());
  std::set_intersection(v.begin(), v.end(), from_map.begin(), from_map.end(),
                        std::back_inserter(intersection));
  v.assign(intersection.begin(), intersection.end());
  vector_to_map<T>(m, intersection);
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
