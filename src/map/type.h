#ifndef CPP2_S21_CONTAINERS_MAP_TYPE_H_
#define CPP2_S21_CONTAINERS_MAP_TYPE_H_
#include <iostream>

template <typename PairType, typename CompareType>
struct PairCompare {
  using Pair_t = PairType;
  using Compare_t = CompareType;

  Compare_t m_compare_;

  int operator()(const Pair_t &left, const Pair_t &right) const {
    return m_compare_(left.first, right.first);
  }
};

#endif  // CPP2_S21_CONTAINERS_MAP_TYPE_H_
