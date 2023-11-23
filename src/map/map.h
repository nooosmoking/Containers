#ifndef CPP2_S21_CONTAINERS_S21_MAP_H_
#define CPP2_S21_CONTAINERS_S21_MAP_H_

#include <functional>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

#include "iter_map.h"
#include "shared_pool.h"
#include "tree.h"

namespace s21 {

template <typename KeyType, typename ValueType,
          typename CompareType = std::less<KeyType>,
          template <typename> typename AllocatorFamily = std::allocator>
class map {
  using key_type = KeyType;
  using mapped_type = ValueType;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using Compare_t = CompareType;
  using DataCompare_ = PairCompare<value_type, Compare_t>;
  using node_ = RBTreeNode<value_type>;
  using tree_ = RBTree<node_, DataCompare_>;
  using m_allocator__t = AllocatorFamily<node_>;
  using const_reference = const value_type &;
  using iterator = MapIterator<node_>;
  using const_iterator = MapConstIterator<node_>;
  using size_type = size_t;
  using shared_pool_t = SharedPtrPoolVector<node_, m_allocator__t>;

 public:
  map() {}

  explicit map(std::initializer_list<value_type> const &items) {
    auto m_root = this->begin();
    for (auto const &item : items) {
      m_root = insert(item).first;
    }
  }

  explicit map(const map &m) {
    auto m_root = this->end();
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
      m_root = insert(*i).first;
    }
  }

  explicit map(map &&m) {
    if (this != &m) {
      m_allocator_ = std::move(m.m_tree_);
    }
  }

  reference operator=(map &&m) {
    if (this != &m) {
      m_allocator_ = std::move(m.m_tree_);
    }
    return *this;
  }

  ~map() {
    for (auto i = begin(); i != end(); ++i) {
      erase(i);
    }
  };

 public:
  mapped_type &at(const key_type &key) {
    iterator pair = this->find(key);
    if (pair.Null()) {
      throw std::out_of_range(
          "s21::map::at: No element exists with key equivalent to key");
    } else {
      return (*pair).second;
    }
  }

  mapped_type operator[](const key_type &key) { return find(key)->second; }

  const mapped_type &at(const key_type &key) const {
    return const_cast<map *>(this)->at(key);
  }

 public:
  void clear() {
    while (!empty()) {
      iterator iter = begin();
      erase(iter);
    }
  }

  bool empty() const { return m_tree_.IsEmpty(); }

  size_t size() const { return m_tree_.GetSize(); }

  size_t max_size() const { return m_tree_.GetSize(); }

 public:
  const_iterator cbegin() const {
    const auto node = m_tree_.CFirst();
    return const_iterator(node);
  }

  iterator begin() {
    auto node = m_tree_.First();
    return iterator(node);
  }

  const_iterator cend() const { return const_iterator(); }

  iterator end() { return iterator(); }

  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &value) {
    auto node = CreateNode();
    node->m_value.first = key;
    node->m_value.second = value;
    const auto ret = m_tree_.InsertUnique(node);
    return std::pair<iterator, bool>(iterator(ret.first), ret.second);
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    return insert(value.first, value.second);
  }
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
    iterator result = m_tree_->Find(value_type{key, obj});

    if (!IsNull(result)) {
      return m_tree_->insert(value_type{key, obj});
    }

    (*result).second = obj;

    return {result, false};
  }

  void erase(iterator it) {
    if (it != end()) {
      m_tree_.Remove(it.Node());
    }
  }

  void erase(const key_type &key) {
    auto iter = find(key);
    if (iter != end()) {
      erase(iter);
    }
  }

  void swap(map &other) noexcept { std::swap(m_tree_, other.m_tree_); }

  bool contains(const key_type &key) noexcept { return !(find(key).Null()); }

  void merge(map &other) noexcept {
    for (auto i = other.cbegin(); i != other.cend(); ++i) {
      insert(*i);
    }
  }

  iterator find(const key_type &key) {
    value_type data;
    data.first = key;
    node_ *node = m_tree_.Search(data);
    return iterator(node);
  }

 private:
  node_ *CreateNode() { return m_pool_.add(node_()).get(); }

 private:
  shared_pool_t m_pool_;
  m_allocator__t m_allocator_;
  tree_ m_tree_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_H_
