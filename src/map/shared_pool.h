#ifndef CPP2_S21_CONTAINERS_MAP_SHARED_POOL_H_
#define CPP2_S21_CONTAINERS_MAP_SHARED_POOL_H_

#include <memory>

#include "../s21_vector.h"

template <typename T, typename Alloc = std::allocator<T>>
class SharedPtrPoolVector {
 public:
  using AllocatorType = typename std::allocator_traits<
      Alloc>::template rebind_alloc<std::shared_ptr<T>>;

  // Default constructor
  SharedPtrPoolVector() {}
  // Copy constructor
  SharedPtrPoolVector(const SharedPtrPoolVector &other) {
    pool_.reserve(other.size());
    for (const auto &obj : other.pool_) {
      pool_.push_back(std::allocate_shared<T, AllocatorType>(allocator_, *obj));
    }
  }

  // Move constructor
  SharedPtrPoolVector(SharedPtrPoolVector &&other) noexcept
      : pool_(std::move(other.pool_)),
        allocator_(std::move(other.allocator_)) {}

  // Assignment operator
  SharedPtrPoolVector &operator=(const SharedPtrPoolVector &other) {
    if (this != &other) {
      pool_.clear();
      pool_.reserve(other.size());
      for (const auto &obj : other.pool_) {
        pool_.push_back(
            std::allocate_shared<T, AllocatorType>(allocator_, *obj));
      }
    }
    return *this;
  }

  // Add an object to the pool
  std::shared_ptr<T> add(const T &object) {
    auto obj = std::allocate_shared<T, AllocatorType>(allocator_, object);
    pool_.push_back(obj);
    return obj;
  }

  // Remove an object from the pool
  void remove(size_t index) {
    if (index < pool_.size()) {
      pool_.erase(pool_.begin() + index);
    }
  }

  // Access an object in the pool
  std::shared_ptr<T> get(size_t index) const {
    if (index < pool_.size()) {
      return pool_[index];
    }
    return nullptr;
  }

  // Get the size of the pool
  size_t size() const { return pool_.size(); }

 private:
  s21::vector<std::shared_ptr<T>> pool_;
  AllocatorType allocator_;
};
#endif  // CPP2_S21_CONTAINERS_MAP_SHARED_POOL_H_
