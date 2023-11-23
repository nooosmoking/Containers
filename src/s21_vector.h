#ifndef CPP2_S21_CONTAINERS_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_S21_VECTOR_H_

#include <err.h>

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  // Member functions
 public:
  vector() {}

  explicit vector(size_type size) {
    size_ = size;
    capacity_ = size;
    buffer_ = nullptr;
    if (size > 0) {
      buffer_ = new value_type[capacity_];
    }
  }

  explicit vector(std::initializer_list<value_type> const &init)
      : size_{init.size()},
        capacity_(init.size()),
        buffer_{new value_type[capacity_]} {
    std::copy(init.begin(), init.end(), buffer_);
  }

  vector(const vector &v) {
    size_ = v.size_;
    capacity_ = v.capacity_;
    buffer_ = nullptr;
    if (size_ > 0) {
      buffer_ = new value_type[capacity_];
    }
    std::copy(v.begin(), v.end(), buffer_);
  }

  vector(vector &&v) noexcept {
    size_ = std::exchange(v.size_, 0);
    capacity_ = std::exchange(v.capacity_, 0);
    buffer_ = std::exchange(v.buffer_, nullptr);
  }

  ~vector() { delete[] buffer_; }

  constexpr vector &operator=(vector &&rhs) noexcept {
    if (this != &rhs) {
      size_ = std::exchange(rhs.size_, 0);
      capacity_ = std::exchange(rhs.capacity_, 0);
      buffer_ = std::exchange(rhs.buffer_, nullptr);
    }

    return *this;
  }

  constexpr vector &operator=(const vector &rhs) {
    if (this != &rhs) {
      delete[] buffer_;

      if (rhs.size_ > 0) {
        buffer_ = new value_type[rhs.capacity_];
        std::copy(rhs.begin(), rhs.end(), buffer_);
      }
      size_ = rhs.size_;
      capacity_ = rhs.capacity_;
    }

    return *this;
  }
  // Element Access
 public:
  constexpr reference at(size_type pos) {
    if (pos >= size_)
      throw std::out_of_range("s21::vector::at The index is out of range");

    return buffer_[pos];
  }

  constexpr const_reference at(size_type pos) const {
    if (pos >= size_)
      throw std::out_of_range("s21::vector::at The index is out of range");

    return buffer_[pos];
  }

  constexpr reference operator[](size_type pos) { return at(pos); }

  constexpr const_reference operator[](size_type pos) const { return at(pos); }

  constexpr reference front() {
    if (size_ == 0)
      throw std::out_of_range(
          "s21::vector::front Using methods on a "
          "zero sized container results "
          "in the UB");
    return *begin();
  }

  constexpr const_reference front() const {
    if (size_ == 0)
      throw std::out_of_range(
          "s21::vector::front Using methods on a "
          "zero sized container results "
          "in the UB");
    return *begin();
  }

  constexpr reference back() {
    if (size_ == 0)
      throw std::out_of_range(
          "s21::vector::back Using methods on a zero "
          "sized container results "
          "in the UB");
    return *std::prev(end());
  }

  constexpr const_reference back() const {
    if (size_ == 0)
      throw std::out_of_range(
          "s21::vector::back Using methods on a zero "
          "sized container results "
          "in the UB");
    return *std::prev(end());
  }

  constexpr iterator data() noexcept { return buffer_; }

  constexpr const_iterator data() const noexcept { return buffer_; }

  // Iterators
  constexpr iterator begin() noexcept { return buffer_; }

  constexpr const_iterator begin() const noexcept { return buffer_; }

  constexpr iterator end() noexcept { return buffer_ + size_; }

  constexpr const_iterator end() const noexcept { return buffer_ + size_; }

  // Capacity
 public:
  bool empty() const noexcept { return begin() == end(); }

  constexpr size_type size() const noexcept {
    return std::distance(begin(), end());
  }

  constexpr size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }

  constexpr void reserve(size_type new_cap) {
    if (new_cap <= capacity_) return;

    if (new_cap > max_size())
      throw std::length_error(
          "s21::vector::reserve Reserve capacity can't be larger than "
          "Vector<T>::max_size()");

    ReallocVector(new_cap);
  }

  constexpr size_type capacity() const noexcept { return capacity_; }

  constexpr void shrink_to_fit() {
    if (capacity_ == size_) return;

    ReallocVector(size_);
  }

  constexpr void clear() noexcept { size_ = 0; }

  constexpr iterator insert(const_iterator pos, value_type &&value) {
    size_type index = pos - begin();
    if (index > size_)
      throw std::out_of_range(
          "s21::vector::insert Unable to insert into a position out of "
          "range of begin() to end()");

    if (size_ == capacity_) ReallocVector(size_ ? size_ * 2 : 1);

    std::copy(begin() + index, end(), begin() + index + 1);
    *(buffer_ + index) = std::move(value);

    ++size_;
    return begin() + index;
  }

  constexpr iterator insert(const_iterator pos, const_reference value) {
    size_type index = pos - begin();
    if (index > size_)
      throw std::out_of_range(
          "s21::vector::insert Unable to insert into a position out of "
          "range of begin() to end()");

    if (size_ == capacity_) ReallocVector(size_ ? size_ * 2 : 1);

    std::copy(begin() + index, end(), begin() + index + 1);
    *(buffer_ + index) = value;

    ++size_;
    return begin() + index;
  }

  constexpr iterator erase(const_iterator pos) {
    size_type index = pos - begin();
    if (index >= size_)
      throw std::out_of_range(
          "s21::vector::erase Unable to erase a position out of range of "
          "begin() to end()");

    std::copy(begin(), const_cast<iterator>(pos), buffer_);
    std::copy(const_cast<iterator>(pos) + 1, end(), buffer_ + index);

    --size_;
    return begin() + index;
  }

  constexpr void push_back(const_reference value) {
    if (size_ == capacity_) reserve(size_ ? size_ * 2 : 1);

    buffer_[size_] = value;
    ++size_;
  }

  constexpr void push_back(value_type &&value) {
    if (size_ == capacity_) reserve(size_ ? size_ * 2 : 1);

    buffer_[size_] = std::move(value);
    ++size_;
  }

  constexpr void pop_back() {
    if (size_ == 0)
      throw std::length_error(
          "s21::vector::pop_back Calling pop_back on an empty container "
          "results in UB");
    --size_;
  }

  constexpr void swap(vector &other) noexcept {
    std::swap(buffer_, other.buffer_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

 private:
  size_type size_ = 0;
  size_type capacity_ = 0;
  iterator buffer_ = nullptr;

  void ReallocVector(size_type new_capacity) {
    iterator tmp = new value_type[new_capacity];
    for (size_type i = 0; i < size_; ++i) tmp[i] = std::move(buffer_[i]);

    delete[] buffer_;
    buffer_ = tmp;
    capacity_ = new_capacity;
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_VECTOR_H_