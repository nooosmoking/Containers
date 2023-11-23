#ifndef CPP2_S21_CONTAINERS_S21_STACK_H_
#define CPP2_S21_CONTAINERS_S21_STACK_H_

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace s21 {
template <typename T, class Container = std::vector<T>>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 public:
  stack() {}
  stack(std::initializer_list<value_type> const &items)
      : container_(items.begin(), items.end()) {}
  stack(const stack &a) { container_ = a.container_; }
  stack(stack &&a) : container_(std::move(a.container_)) {}
  ~stack() {}

  stack &operator=(const stack &a) {
    if (this != &a) container_ = a.container_;
    return *this;
  }
  stack &operator=(stack &&a) {
    if (this != &a) container_ = std::move(a.container_);
    return *this;
  }

  const_reference top() const { return container_.back(); }

  bool empty() const { return container_.empty(); }
  size_type size() const { return container_.size(); }

  void push(const_reference value) { container_.push_back(value); }
  void pop() { container_.pop_back(); }
  void swap(stack &other) { std::swap(container_, other.container_); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    for (const auto &arg : {args...}) {
      container_.push_back(arg);
    }
  }

 private:
  Container container_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_STACK_H_