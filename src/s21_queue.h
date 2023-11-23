#ifndef CPP2_S21_CONTAINERS_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_S21_QUEUE_H_

#include <iostream>

#include "s21_list.h"
namespace s21 {

template <typename T, typename container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() {}

  queue(std::initializer_list<value_type> const &items) : container_(items) {}

  ~queue() {}

  queue(const queue &q) : container_(q.container_) {}

  queue &operator=(const queue &q) {
    container_ = q.container_;
    return *this;
  }

  queue(queue &&q) { container_.swap(q.container_); }

  queue &operator=(queue &&q) {
    if (this != &q) {
      container_.clear();
      swap(q);
    }
    return *this;
  }

  const_reference front() { return container_.front(); }

  const_reference back() { return container_.back(); }

  bool empty() { return container_.empty(); }

  size_type size() { return container_.size(); }
  void push(const_reference value) { container_.push_back(value); }

  void pop() { container_.pop_front(); }

  void swap(queue &other) { container_.swap(other.container_); }

 private:
  container container_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_QUEUE_H_