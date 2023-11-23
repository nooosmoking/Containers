#ifndef CPP2_S21_CONTAINERS_TREE_H_
#define CPP2_S21_CONTAINERS_TREE_H_

#include <functional>
#include <memory>
#include <tuple>
#include <utility>

enum class NodeColor { RED, BLACK };

template <typename Key>
struct Node {
  Node *left, *right, *parent;
  Key key;
  NodeColor color;
  Node() {}
  Node(Node *left, Node *right, Node *parent, Key key, NodeColor color)
      : left(left), right(right), parent(parent), key(key), color(color) {}
  Node(const Node &other) = default;
  Node(Node &&other) = default;
  constexpr Node &operator=(const Node &other) = default;
  ~Node() = default;
};

template <typename Key>
NodeColor GetColor(Node<Key> *node_pointer) {
  return (node_pointer == nullptr) ? NodeColor::BLACK : node_pointer->color;
}

template <typename Key, typename Comparator = std::less<Key>,
          typename Allocator = std::allocator<Key>>
class RBTree {
 public:
  using value_type = Key;
  using node_type = Node<Key>;
  using node_pointer = node_type *;
  using node_ppointer = node_type **;
  using tree_pointer = RBTree<Key, Comparator, Allocator> *;
  using const_tree_pointer = const RBTree<Key, Comparator, Allocator> *;
  using Alloc = Allocator;
  using NodeAlloc =
      typename std::allocator_traits<Alloc>::template rebind_alloc<Node<Key>>;

  class TreeIterator {
   public:
    using value_type = Key;
    using node_type = Node<Key>;
    using node_pointer = node_type *;
    using tree_pointer = RBTree<Key, Comparator, Allocator> *;
    using iterator = RBTree<Key, Comparator, Allocator>::TreeIterator;
    TreeIterator() : tree_(nullptr), it_(nullptr) {}
    TreeIterator(tree_pointer other_tree, node_pointer other_it)
        : tree_(other_tree), it_(other_it) {
      if (it_ == nullptr) it_ = tree_->end_;
    }
    TreeIterator(const iterator &other) : tree_(other.tree_), it_(other.it_) {}
    TreeIterator(iterator &&other) : tree_(other.tree_), it_(other.it_) {
      other.tree_ = nullptr;
      other.it_ = nullptr;
    }
    ~TreeIterator() = default;
    iterator &operator=(const iterator &other) {
      if (this != &other) {
        tree_ = other.tree_;
        it_ = other.it_;
      }
      return *this;
    }
    iterator &operator=(iterator &&other) {
      if (this != &other) {
        tree_ = std::exchange(other.tree_, nullptr);
        it_ = std::exchange(other.it_, nullptr);
      }
      return *this;
    }
    node_pointer it() const { return (it_ == tree_->end_) ? nullptr : it_; }
    iterator &operator++() {
      if (it_ != tree_->end_)
        it_ = tree_->Next(it_);
      else
        it_ = tree_->Last();
      if (it_ == nullptr) it_ = tree_->end_;
      return *this;
    }
    const iterator operator++(int) {
      RBTree<Key, Comparator, Allocator>::TreeIterator foo(*this);
      ++(*this);
      return foo;
    }
    iterator &operator--() {
      if (it_ != tree_->end_)
        it_ = tree_->Prev(it_);
      else
        it_ = tree_->Last();
      if (it_ == nullptr) it_ = tree_->end_;
      return *this;
    }
    const iterator operator--(int) {
      TreeIterator foo(*this);
      --(*this);
      return foo;
    }
    bool operator==(const iterator &other) const { return it_ == other.it_; }
    bool operator!=(const iterator &other) const { return it_ != other.it_; }
    const value_type &operator*() const { return it_->key; }

   protected:
    tree_pointer tree_;
    node_pointer it_;
  };
  class ConstTreeIterator {
   public:
    using value_type = Key;
    using node_type = Node<Key>;
    using node_pointer = node_type *;
    using const_tree_pointer = const RBTree<Key, Comparator, Allocator> *;
    using iterator = RBTree<Key, Comparator, Allocator>::TreeIterator;
    using const_iterator =
        RBTree<Key, Comparator, Allocator>::ConstTreeIterator;
    ConstTreeIterator() : tree_(nullptr), it_(nullptr) {}
    ConstTreeIterator(const_tree_pointer other_tree, node_pointer other_it)
        : tree_(other_tree), it_(other_it) {
      if (it_ == nullptr) it_ = tree_->end_;
    }
    ConstTreeIterator(const const_iterator &other)
        : tree_(other.tree_), it_(other.it_) {}
    ConstTreeIterator(const_iterator &&other)
        : tree_(other.tree_), it_(other.it_) {
      other.tree_ = nullptr;
      other.it_ = nullptr;
    }
    ~ConstTreeIterator() = default;
    const_iterator &operator=(const const_iterator &other) {
      if (this != &other) {
        tree_ = other.tree_;
        it_ = other.it_;
      }
      return *this;
    }
    const_iterator &operator=(const_iterator &&other) {
      if (this != &other) {
        tree_ = std::exchange(other.tree_, nullptr);
        it_ = std::exchange(other.it_, nullptr);
      }
      return *this;
    }
    node_pointer it() const { return (it_ == tree_->end_) ? nullptr : it_; }
    const_iterator &operator++() {
      if (it_ != tree_->end_)
        it_ = tree_->Next(it_);
      else
        it_ = tree_->Last();
      if (it_ == nullptr) it_ = tree_->end_;
      return *this;
    }
    const const_iterator operator++(int) {
      RBTree<Key, Comparator, Allocator>::ConstTreeIterator foo(*this);
      ++(*this);
      return foo;
    }
    const_iterator &operator--() {
      if (it_ != tree_->end_)
        it_ = tree_->Prev(it_);
      else
        it_ = tree_->Last();
      if (it_ == nullptr) it_ = tree_->end_;
      return *this;
    }
    const const_iterator operator--(int) {
      ConstTreeIterator foo(*this);
      --(*this);
      return foo;
    }
    bool operator==(const const_iterator &other) const {
      return it_ == other.it_;
    }
    bool operator!=(const const_iterator &other) const {
      return it_ != other.it_;
    }

    const value_type &operator*() const { return it_->key; }

   protected:
    const_tree_pointer tree_;
    node_pointer it_;
  };
  using iterator = RBTree<Key, Comparator, Allocator>::TreeIterator;
  using const_iterator = RBTree<Key, Comparator, Allocator>::ConstTreeIterator;
  RBTree() : root_(nullptr), size_(0) { end_ = alloc_.allocate(1); }
  RBTree(const Comparator &comp, const Allocator &alloc)
      : alloc_(alloc), comp_(comp), root_(nullptr), size_(0) {
    end_ = alloc_.allocate(1);
  }
  RBTree(const RBTree &other) : RBTree(other.comp_, other.alloc_) {
    if (!other.Empty()) {
      // end_ = alloc_.allocate(1);
      root_ = AllocAndConstruct(nullptr, other.root_->key, other.root_->color);
      CopyTree(root_, other.root_);
    }
    size_ = other.size_;
  }
  RBTree(RBTree &&other) : root_(nullptr), end_(nullptr), size_(0) {
    *this = std::move(other);
  }
  RBTree &operator=(const RBTree &other) {
    if (this == &other) return *this;
    *this = std::move(RBTree(other));
    return *this;
  }
  RBTree &operator=(RBTree &&other) {
    if (this != &other) {
      root_ = std::exchange(other.root_, root_);
      end_ = std::exchange(other.end_, end_);
      size_ = std::exchange(other.size_, size_);
      comp_ = std::exchange(other.comp_, comp_);
      alloc_ = std::exchange(other.alloc_, alloc_);
    }
    return *this;
  }
  ~RBTree() {
    if (!Empty()) DeleteTree(&root_);
    alloc_.deallocate(end_, 1);
  }

  bool Empty() const { return root_ == nullptr; }
  size_t size() const { return size_; }
  virtual size_t Count(const Key &key) const {
    if (Empty()) return 0;
    node_pointer current = Find(key);
    if (current == nullptr)
      return 0;
    else
      return 1;
  }
  const iterator End(tree_pointer this_tree) {
    return iterator(this_tree, end_);
  }
  const const_iterator End(const_tree_pointer this_tree) const {
    return const_iterator(this_tree, end_);
  }
  std::pair<iterator, bool> Insert(const Key &key) {
    if (!Empty()) {
      bool add_flag = false, incert_left = true;
      node_pointer current = root_;
      std::tie(add_flag, incert_left, current) = InsertInside(key);
      if (add_flag) {
        ++size_;
        if (incert_left) {
          current->left = AllocAndConstruct(current, key, NodeColor::RED);
          current = current->left;
        } else {
          current->right = AllocAndConstruct(current, key, NodeColor::RED);
          current = current->right;
        }
        if (GetColor(current->parent) == NodeColor::RED)
          BalanceTreeIncert(current);
      }
      return std::make_pair(iterator(this, current), add_flag);
    } else {
      root_ = AllocAndConstruct(nullptr, key, NodeColor::BLACK);
      size_ = 1;
      return std::make_pair(iterator(this, root_), true);
    }
  }
  void Remove(node_pointer node) {
    if (node == nullptr) return;
    if (node->color == NodeColor::RED && node->left == nullptr &&
        node->right == nullptr) {
      if (node->parent->left == node) {
        node->parent->left = nullptr;
      } else {
        node->parent->right = nullptr;
      }
      DestroyAndDelete(&node);
      --size_;
      return;
    }
    if (node->left != nullptr && node->right != nullptr) {
      node_pointer min_max = FindLeftMax(node);
      std::swap(node->key, min_max->key);
      Remove(min_max);
      return;
    }
    if (node->left != nullptr) {
      std::swap(node->key, node->left->key);
      Remove(node->left);
      return;
    }
    if (node->right != nullptr) {
      std::swap(node->key, node->right->key);
      Remove(node->right);
      return;
    }
    if (node == root_) {
      DestroyAndDelete(&root_);
      size_ = 0;
      return;
    }
    if (node->parent->left == node)
      node->parent->left = nullptr;
    else
      node->parent->right = nullptr;
    BalanceTreeRemove(node->parent, node->parent->left == nullptr);
    DestroyAndDelete(&node);
    --size_;
  }
  void Swap(RBTree &other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    std::swap(end_, other.end_);
    std::swap(comp_, other.comp_);
    std::swap(alloc_, other.alloc_);
  }
  void Merge(RBTree &other) {
    if (Empty()) {
      std::swap(other.root_, root_);
      std::swap(other.size_, size_);
      return;
    }
    if (other.Empty()) return;
    RBTree<Key, Comparator, Allocator> remaining;
    SplitTree(other.root_, &remaining);
    other.root_ = nullptr;
    std::swap(other.root_, remaining.root_);
    std::swap(other.size_, remaining.size_);
  }
  virtual node_pointer Find(const Key &key) const {
    node_pointer current = root_;
    while (current != nullptr) {
      if (IsEqual(key, current->key)) return current;
      if (comp_(key, current->key))
        current = current->left;
      else
        current = current->right;
    }
    return nullptr;
  }
  node_pointer First() const {
    if (!Empty()) {
      node_pointer current = root_;
      while (current->left != nullptr) {
        current = current->left;
      }
      return current;
    }
    return nullptr;
  }
  node_pointer Last() const {
    if (!Empty()) {
      node_pointer current = root_;
      while (current->right != nullptr) {
        current = current->right;
      }
      return current;
    }
    return nullptr;
  }
  void Clear() {
    DeleteTree(&root_);
    size_ = 0;
  }

 protected:
  NodeAlloc alloc_;
  Comparator comp_;
  node_pointer root_;
  node_pointer end_;
  size_t size_;

  bool IsEqual(const Key &a, const Key &b) const {
    return !comp_(a, b) && !comp_(b, a);
  }
  void DeleteTree(node_ppointer node) {
    if (*node != nullptr) {
      DeleteTree(&((*node)->left));
      DeleteTree(&((*node)->right));
      DestroyAndDelete(node);
    }
  }
  node_pointer Grandparent(node_pointer node) const {
    return (node != nullptr && node->parent != nullptr) ? node->parent->parent
                                                        : nullptr;
  }
  std::tuple<bool, bool, node_pointer> InsertInside(const Key &key) {
    node_pointer current = root_;
    bool add_flag = false, incert_left = true;
    while (true) {
      if (comp_(key, current->key)) {
        if (current->left == nullptr) {
          add_flag = true;
          break;
        } else {
          current = current->left;
        }
      } else {
        if (!comp_(current->key, key)) break;
        if (current->right == nullptr) {
          add_flag = true;
          incert_left = false;
          break;
        } else {
          current = current->right;
        }
      }
    }
    return std::make_tuple(add_flag, incert_left, current);
  }
  void SplitTree(node_pointer other_node,
                 RBTree<Key, Comparator, Allocator> *remaining) {
    if (other_node == nullptr) return;
    SplitTree(other_node->left, remaining);
    SplitTree(other_node->right, remaining);
    bool add_flag = false, incert_left = true;
    node_pointer current = root_;
    std::tie(add_flag, incert_left, current) = InsertInside(other_node->key);
    if (add_flag) {
      ++size_;
      other_node->color = NodeColor::RED;
      other_node->parent = current;
      other_node->left = other_node->right = nullptr;
      if (incert_left)
        current->left = other_node;
      else
        current->right = other_node;
      if (GetColor(current) == NodeColor::RED) BalanceTreeIncert(other_node);
    } else {
      if (remaining->Empty()) {
        remaining->size_ = 1;
        other_node->color = NodeColor::BLACK;
        other_node->parent = nullptr;
        other_node->left = other_node->right = nullptr;
        remaining->root_ = other_node;
      } else {
        node_pointer remaining_current = remaining->root_;
        std::tie(add_flag, incert_left, remaining_current) =
            remaining->InsertInside(other_node->key);
        ++remaining->size_;
        other_node->color = NodeColor::RED;
        other_node->parent = remaining_current;
        other_node->left = other_node->right = nullptr;
        if (incert_left)
          remaining_current->left = other_node;
        else
          remaining_current->right = other_node;
        if (GetColor(remaining_current) == NodeColor::RED)
          remaining->BalanceTreeIncert(other_node);
      }
    }
  }
  node_pointer Uncle(node_pointer node) const {
    node_pointer gparent = Grandparent(node);
    if (gparent == nullptr) return nullptr;
    return (gparent->right == node->parent) ? gparent->left : gparent->right;
  }
  node_pointer AllocAndConstruct(node_pointer parent, Key key,
                                 NodeColor color) {
    node_pointer newNode = alloc_.allocate(1);
    alloc_.construct(newNode, Node<Key>(nullptr, nullptr, parent, key, color));
    return newNode;
  }
  void DestroyAndDelete(node_ppointer node) {
    alloc_.destroy(*node);
    alloc_.deallocate(*node, 1);
    *node = nullptr;
  }
  void CopyTree(node_pointer node, node_pointer other) {
    if (other->left != nullptr) {
      node->left =
          AllocAndConstruct(node, other->left->key, other->left->color);
      CopyTree(node->left, other->left);
    }
    if (other->right != nullptr) {
      node->right =
          AllocAndConstruct(node, other->right->key, other->right->color);
      CopyTree(node->right, other->right);
    }
  }
  void RotateLeft(node_pointer node) {
    node->color = node->parent->color;
    node->parent->color = NodeColor::RED;
    node->parent->right = node->left;
    if (node->left != nullptr) node->left->parent = node->parent;
    node->left = node->parent;
    node->parent = node->parent->parent;
    if (node->parent != nullptr) {
      if (node->parent->left == node->left) {
        node->parent->left = node;
      } else {
        node->parent->right = node;
      }
    } else {
      root_ = node;
    }
    node->left->parent = node;
  }
  void RotateRight(node_pointer node) {
    node->color = node->parent->color;
    node->parent->color = NodeColor::RED;
    node->parent->left = node->right;
    if (node->right != nullptr) node->right->parent = node->parent;
    node->right = node->parent;
    node->parent = node->parent->parent;
    if (node->parent != nullptr) {
      if (node->parent->right == node->right) {
        node->parent->right = node;
      } else {
        node->parent->left = node;
      }
    } else {
      root_ = node;
    }
    node->right->parent = node;
  }
  void BalanceTreeIncert(node_pointer current) {
    node_pointer uncle = Uncle(current);
    if (GetColor(uncle) == NodeColor::RED) {
      uncle->color = NodeColor::BLACK;
      current->parent->color = NodeColor::BLACK;
      if (current->parent->parent != root_) {
        current->parent->parent->color = NodeColor::RED;
        if (GetColor(current->parent->parent->parent) == NodeColor::RED) {
          BalanceTreeIncert(current->parent->parent);
        }
      }
    } else {
      if (current == current->parent->left) {
        if (current->parent == current->parent->parent->right) {
          RotateRight(current);
          RotateLeft(current);
        } else {
          RotateRight(current->parent);
        }
      } else {
        if (current->parent == current->parent->parent->left) {
          RotateLeft(current);
          RotateRight(current);
        } else {
          RotateLeft(current->parent);
        }
      }
    }
  }
  void BalanceTreeRemove(node_pointer parent, bool delete_left) {
    node_pointer bro = (delete_left) ? parent->right : parent->left;
    if (GetColor(bro) == NodeColor::RED) {
      if (delete_left)
        RotateLeft(bro);
      else
        RotateRight(bro);
      BalanceTreeRemove(parent, delete_left);
      return;
    }
    if (GetColor(bro->left) == NodeColor::RED ||
        GetColor(bro->right) == NodeColor::RED) {
      if (delete_left) {
        if (GetColor(bro->right) == NodeColor::RED) {
          RotateLeft(bro);
          if (bro->right != nullptr) bro->right->color = NodeColor::BLACK;
          if (bro->left != nullptr) bro->left->color = NodeColor::BLACK;
        } else {
          RotateRight(bro->left);
          BalanceTreeRemove(parent, delete_left);
        }
      } else {
        if (GetColor(bro->left) == NodeColor::RED) {
          RotateRight(bro);
          if (bro->right != nullptr) bro->right->color = NodeColor::BLACK;
          if (bro->left != nullptr) bro->left->color = NodeColor::BLACK;
        } else {
          RotateLeft(bro->right);
          BalanceTreeRemove(parent, delete_left);
        }
      }
      return;
    }
    bro->color = NodeColor::RED;
    if (parent == root_) return;
    if (parent->color == NodeColor::RED)
      parent->color = NodeColor::BLACK;
    else
      BalanceTreeRemove(parent->parent, parent->parent->left == parent);
  }

  node_pointer FindLeftMax(node_pointer node) const {
    node_pointer current = node->left;
    if (current != nullptr) {
      while (current->right != nullptr) current = current->right;
    }
    return current;
  }
  node_pointer Next(node_pointer node) const {
    if (node == nullptr) return nullptr;
    if (node->right != nullptr) {
      Node<Key> *current = node->right;
      while (current->left != nullptr) {
        current = current->left;
      }
      return current;
    } else {
      Node<Key> *parent = node->parent;
      while (parent != nullptr && parent->right == node) {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }
  }
  node_pointer Prev(node_pointer node) const {
    if (node == nullptr) return nullptr;
    if (node->left != nullptr) {
      Node<Key> *current = node->left;
      while (current->right != nullptr) {
        current = current->right;
      }
      return current;
    } else {
      Node<Key> *parent = node->parent;
      while (parent != nullptr && parent->left == node) {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }
  }
};

template <typename Key, typename Comparator = std::less<Key>,
          typename Allocator = std::allocator<Key>>
class RBTreeMulti : public RBTree<Key, Comparator, Allocator> {
 public:
  using node_type = Node<Key>;
  using node_pointer = node_type *;
  using base_type = RBTree<Key, Comparator, Allocator>;

  node_pointer Find(const Key &key) const override {
    node_pointer current = base_type::root_;
    while (current != nullptr) {
      if (base_type::IsEqual(key, current->key)) break;
      if (base_type::comp_(key, current->key))
        current = current->left;
      else
        current = current->right;
    }
    if (current == nullptr) return nullptr;
    for (node_pointer i = base_type::Prev(current); i && i->key == key;
         i = base_type::Prev(i))
      current = i;
    return current;
  }
  node_pointer Insert(const Key &key) {
    if (!base_type::Empty()) {
      bool incert_left = true;
      node_pointer current = base_type::root_;
      std::tie(incert_left, current) = InsertInside(key);
      ++base_type::size_;
      if (incert_left) {
        current->left =
            base_type::AllocAndConstruct(current, key, NodeColor::RED);
        current = current->left;
      } else {
        current->right =
            base_type::AllocAndConstruct(current, key, NodeColor::RED);
        current = current->right;
      }
      if (GetColor(current->parent) == NodeColor::RED)
        base_type::BalanceTreeIncert(current);
      return current;
    } else {
      base_type::root_ =
          base_type::AllocAndConstruct(nullptr, key, NodeColor::BLACK);
      base_type::size_ = 1;
      return base_type::root_;
    }
  }
  void Merge(RBTreeMulti &other) {
    if (base_type::Empty()) {
      std::swap(other.root_, base_type::root_);
      std::swap(other.size_, base_type::size_);
      return;
    }
    if (other.Empty()) return;
    ExtractTree(other.root_);
    other.root_ = nullptr;
    other.size_ = 0;
  }
  size_t Count(const Key &key) const override {
    if (base_type::Empty()) return 0;
    node_pointer current = base_type::Find(key);
    if (current == nullptr) return 0;
    int Counter = 1;
    for (node_pointer i = base_type::Prev(current);
         i != nullptr && base_type::IsEqual(key, i->key);
         i = base_type::Prev(i))
      ++Counter;
    for (node_pointer i = base_type::Next(current);
         i != nullptr && base_type::IsEqual(key, i->key);
         i = base_type::Next(i))
      ++Counter;
    return Counter;
  }
  node_pointer LowerBound(const Key &key) const {
    node_pointer current = base_type::root_;
    if (current == nullptr) return base_type::end_;
    node_pointer lastBigCurrent = nullptr;
    while (current != nullptr) {
      if (base_type::IsEqual(key, current->key)) break;
      if (base_type::comp_(key, current->key)) {
        lastBigCurrent = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }
    if (current != nullptr) {
      for (node_pointer i = base_type::Prev(current); i && i->key == key;
           i = base_type::Prev(i))
        current = i;
      return current;
    }
    return (lastBigCurrent == nullptr) ? base_type::end_ : lastBigCurrent;
  }
  node_pointer UpperBound(const Key &key) const {
    node_pointer current = base_type::root_;
    if (current == nullptr) return base_type::end_;
    node_pointer lastBigCurrent = nullptr;
    while (current != nullptr) {
      if (base_type::IsEqual(key, current->key)) break;
      if (base_type::comp_(key, current->key)) {
        lastBigCurrent = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }
    if (current != nullptr) {
      node_pointer i = base_type::Next(current);
      for (; i && i->key == key; i = base_type::Next(i)) current = i;
      return i;
    }
    return (lastBigCurrent == nullptr) ? base_type::end_ : lastBigCurrent;
  }

 protected:
  std::pair<bool, node_pointer> InsertInside(const Key &key) {
    node_pointer current = base_type::root_;
    bool incert_left = true;
    while (true) {
      if (base_type::comp_(key, current->key)) {
        if (current->left == nullptr)
          break;
        else
          current = current->left;
      } else {
        if (current->right == nullptr) {
          incert_left = false;
          break;
        } else {
          current = current->right;
        }
      }
    }
    return std::make_pair(incert_left, current);
  }
  void ExtractTree(node_pointer other_node) {
    if (other_node == nullptr) return;
    ExtractTree(other_node->left);
    ExtractTree(other_node->right);
    other_node->left = other_node->right = nullptr;
    bool incert_left = true;
    node_pointer current = base_type::root_;
    std::tie(incert_left, current) = InsertInside(other_node->key);
    ++base_type::size_;
    other_node->color = NodeColor::RED;
    other_node->parent = current;
    if (incert_left)
      current->left = other_node;
    else
      current->right = other_node;
    if (GetColor(current) == NodeColor::RED)
      base_type::BalanceTreeIncert(other_node);
  }
};

#endif  // CPP2_S21_CONTAINERS_TREE_H_
