#ifndef CPP2_S21_CONTAINERS_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_S21_ARRAY_H_

#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 public:
  // Support for zero-sized arrays mandatory.

  array() {
    for (size_type i = 0; i < size_; ++i) {
      array_[i] = value_type{};
    }
  }
  array(std::initializer_list<value_type> const &items) {
    size_type i = 0;
    for (auto it = items.begin(); it != items.end(); ++it, ++i) {
      array_[i] = *it;
    }
    for (; i < size_; ++i) {
      array_[i] = value_type{};
    }
  }
  array(const array &a) { std::copy(a.cbegin(), a.cend(), array_); }
  array(array &&a) : size_(a.size_) { std::move(a.begin(), a.end(), array_); }
  ~array() {}

  array &operator=(const array &a) {
    if (this != &a) std::copy(a.cbegin(), a.cend(), array_);
    return *this;
  }
  array &operator=(array &&a) {
    if (this != &a) std::move(a.begin(), a.end(), array_);
    return *this;
  }
  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("array::at out of range");
    return array_[pos];
  }
  const_reference at(size_type pos) const {
    if (pos >= size_) throw std::out_of_range("array::at out of range");
    return array_[pos];
  }
  reference operator[](size_type pos) noexcept { return array_[pos]; }
  const_reference operator[](size_type pos) const noexcept {
    return array_[pos];
  }
  const_reference front() const { return array_[0]; }
  const_reference back() const { return array_[size_ - 1]; }
  iterator data() noexcept { return array_; }
  const_iterator data() const noexcept { return array_; }

  iterator begin() noexcept { return array_; }
  iterator end() noexcept { return &array_[size_]; }
  const_iterator cbegin() const noexcept { return array_; }
  const_iterator cend() const noexcept { return &array_[size_]; }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept { return size_; }

  void swap(array &other) noexcept { std::swap(*this, other); }
  void fill(const_reference value) { std::fill(begin(), end(), value); }

 private:
  const size_type size_ = N;
  value_type array_[N ? N : 1];
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_ARRAY_H_