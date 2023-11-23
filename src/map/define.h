#ifndef CPP2_S21_CONTAINERS_MAP_DEFINE_H_
#define CPP2_S21_CONTAINERS_MAP_DEFINE_H_

#include <cassert>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

template <typename T>
inline bool IsNull(const T *const ptr) {
  return nullptr == ptr;
}

template <typename T>
inline bool IsNull(const T &val) {
  return nullptr == val;
}

#endif  // CPP2_S21_CONTAINERS_MAP_DEFINE_H_
