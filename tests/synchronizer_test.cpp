//
// Created by Gueren Drive on 4/16/21.
//

#include <vector>
#include <map>

#include "gtest/gtest.h"
#include "utils.hpp"
#include "synchronizer.hpp"

TEST(EmptyVector, synchronizer) {
  std::vector<int>   v;
  std::map<int, int> m;

  v.reserve(50);
  for (int i = 0; i < 50; ++i) {
    v.push_back(random_value(9));
  }
  synchronize(v, m);
  ASSERT_TRUE(v.empty());
}

TEST(EmptyMap, synchronizer) {
  std::vector<int>   v;
  std::map<int, int> m;

  for (int i = 0; i < 50; ++i) {
    m[i] = random_value(9);
  }
  synchronize(v, m);
  ASSERT_TRUE(m.empty());
}

TEST(NoCouples, synchronizer) {
  std::vector<int>   v;
  std::map<int, int> m;

  v.reserve(50);
  for (int i = 0; i < 50; ++i) {
    v.push_back(i);
    m[i] = i + 50;
  }
  synchronize(v, m);
  ASSERT_TRUE(v.empty());
  ASSERT_TRUE(m.empty());
}

TEST(BigSize, synchronizer) {
  std::vector<int>   v;
  std::map<int, int> m;

  v.reserve(10000);
  for (int i = 0; i < 10000; ++i) {
    v.push_back(random_value(9));
    m[i] = random_value();
  }

  synchronize(v, m);
  ASSERT_EQ(v.size(), m.size());
  for (int i = 0; i < v.size(); ++i) {
    ASSERT_EQ(v.at(i), m.at(i));
  }
}
