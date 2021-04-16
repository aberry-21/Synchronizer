//
// Created by Gueren Drive on 4/16/21.
//

#pragma once

#ifndef UNION_SYNCHRONIZER_HPP
#define UNION_SYNCHRONIZER_HPP

# include <vector>
# include <map>
# include <algorithm>

template <class T>
void map_to_vector(std::vector<T> &v, const std::map<int, T> &m) {
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
void vector_to_map(std::map<int, T> &m, std::vector<T> &v) {
  m.clear();
  for (int i = 0; i < v.size(); ++i) {
    m[i] = v[i];
  }
}

template <class T>
void synchronize(std::vector<T> &v, std::map<int, T> &m) {
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

#endif //UNION_SYNCHRONIZER_HPP
