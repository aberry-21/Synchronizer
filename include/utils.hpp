//
// Created by Gueren Drive on 4/16/21.
//

#pragma once

#ifndef UNION_UTILS_HPP
#define UNION_UTILS_HPP

# include <iostream>
# include <vector>
# include <map>

int  random_value(int max_value = RAND_MAX, int min_value = 0);

template <class T>
void visualize_vector(const std::vector<T> &v) {
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
void visualize_map(const std::map<int, T> &m) {
  void visualize_map(const std::map<int, T> &m);
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
void vector_random_remove_one(std::vector<T> &v) {
  v.erase(v.begin() + random_value(v.size() - 1));
}

template <class T>
void map_random_remove_one(std::map<int, T> &m) {
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

#endif //UNION_UTILS_HPP
