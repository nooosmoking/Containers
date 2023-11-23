#ifndef CPP2_S21_CONTAINERS_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_S21_MULTISET_H_
#include <functional>
#include <initializer_list>
#include <memory>
#include <utility>

#include "s21_vector.h"
#include "tree.h"

namespace s21 {

template <typename Key, typename Comparator = std::less<Key>,
          typename Allocator = std::allocator<Key>>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RBTree<Key, Comparator, Allocator>::TreeIterator;
  using const_iterator =
      typename RBTree<Key, Comparator, Allocator>::ConstTreeIterator;
  using size_type = std::size_t;

  multiset() : rb_tree_() {}
  multiset(std::initializer_list<value_type> const &items) : rb_tree_() {
    for (auto i = items.begin(); i != items.end(); ++i) insert(*i);
  }
  multiset(const multiset &s) : rb_tree_(s.rb_tree_) {}
  multiset(multiset &&s) { *this = std::move(s); }
  ~multiset() {}
  multiset &operator=(const multiset &s) {
    rb_tree_ = s.rb_tree_;
    return *this;
  }
  multiset &operator=(multiset &&s) {
    if (this != &s) {
      rb_tree_ = std::move(s.rb_tree_);
    }
    return *this;
  }
  iterator begin() { return iterator(&rb_tree_, rb_tree_.First()); }
  const_iterator begin() const {
    return const_iterator(&rb_tree_, rb_tree_.First());
  }
  iterator end() { return rb_tree_.End(&rb_tree_); }
  const_iterator end() const { return rb_tree_.End(&rb_tree_); }
  bool empty() const { return rb_tree_.Empty(); }
  size_type size() const { return rb_tree_.size(); }
  size_type max_size() const { return rb_tree_.alloc_.max_size(); }
  void clear() { rb_tree_.Clear(); }
  iterator insert(const value_type &value) {
    return iterator(&rb_tree_, rb_tree_.Insert(value));
  }
  void erase(iterator pos) { rb_tree_.Remove(pos.it()); }
  void swap(multiset &other) { rb_tree_.Swap(other.rb_tree_); }
  void merge(multiset &other) { rb_tree_.Merge(other.rb_tree_); }
  iterator find(const value_type &key) {
    return iterator(&rb_tree_, rb_tree_.Find(key));
  }
  const_iterator find(const Key &key) const {
    return const_iterator(&rb_tree_, rb_tree_.Find(key));
  }

  bool contains(const Key &key) const { return rb_tree_.Find(key) != nullptr; }

  size_type count(const Key &key) const { return rb_tree_.Count(key); }

  iterator lower_bound(const Key &key) {
    return iterator(&rb_tree_, rb_tree_.LowerBound(key));
  }
  const_iterator lower_bound(const Key &key) const {
    return const_iterator(&rb_tree_, rb_tree_.LowerBound(key));
  }
  iterator upper_bound(const Key &key) {
    return iterator(&rb_tree_, rb_tree_.UpperBound(key));
  }
  const_iterator upper_bound(const Key &key) const {
    return const_iterator(&rb_tree_, rb_tree_.UpperBound(key));
  }
  std::pair<iterator, iterator> equal_range(const Key &key) {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  std::pair<const_iterator, const_iterator> equal_range(
      const value_type &key) const {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  template <typename... Args>
  s21::vector<iterator> insert_many(Args &&...args) {
    s21::vector<iterator> result;
    insert_many_helper(result, std::forward<Args>(args)...);
    return result;
  }

 protected:
  RBTreeMulti<Key, Comparator, Allocator> rb_tree_;
  template <typename Arg, typename... Args>
  void insert_many_helper(s21::vector<iterator> &result, Arg &&arg,
                          Args &&...args) {
    result.push_back(insert(std::forward<Arg>(arg)));
    insert_many_helper(result, std::forward<Args>(args)...);
  }

  // Base case for recursion
  void insert_many_helper(s21::vector<iterator> &) {}
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MULTISET_H_