#ifndef CPP2_S21_CONTAINERS_MAP_MAPITERATOR_H_
#define CPP2_S21_CONTAINERS_MAP_MAPITERATOR_H_

template <typename NodeType>
class MapIterator {
  using Node_t = NodeType;
  using Value_t = typename Node_t::Value_t;

 public:
  MapIterator() : m_node_(nullptr) {}

  MapIterator(const MapIterator &other) : m_node_(other.m_node_) {}

  MapIterator(Node_t *node) : m_node_(node) {}

  ~MapIterator() {}

  MapIterator &operator=(const MapIterator &other) {
    if (&other != this) {
      m_node_ = other.m_node_;
    }
    return *this;
  }
  bool Null() { return IsNull(m_node_); }

  Node_t *Node() { return m_node_; }

  Value_t &operator*() { return m_node_->m_value; }

  Value_t *operator->() { return &m_node_->m_value; }

  MapIterator &operator++() {
    m_node_ = m_node_->Forward();
    return *this;
  }

  MapIterator &operator++(int) {
    m_node_ = m_node_->Forward();
    return *this;
  }

  MapIterator &operator--() {
    m_node_ = m_node_->Backward();
    return *this;
  }

  MapIterator &operator--(int) {
    m_node_ = m_node_->Backward();
    return *this;
  }

  bool operator==(const MapIterator &other) const {
    return m_node_ == other.m_node_;
  }

  bool operator!=(const MapIterator &other) const {
    return m_node_ != other.m_node_;
  }

 private:
  Node_t *m_node_;
};

template <typename NodeType>
class MapConstIterator {
  using Node_t = NodeType;
  using Value_t = typename Node_t::Value_t;

 public:
  MapConstIterator() : m_node_(nullptr) {}

  MapConstIterator(const MapConstIterator &other) : m_node_(other.m_node_) {}

  MapConstIterator(const Node_t *node) : m_node_(node) {}

  ~MapConstIterator() {}

  MapConstIterator &operator=(const MapConstIterator &other) {
    if (&other != this) {
      m_node_ = other.m_node_;
    }
    return *this;
  }

  const Node_t *Node() const { return m_node_; }

  const Value_t &operator*() const { return m_node_->m_value; }

  const Value_t *operator->() const { return &m_node_->m_value; }

  MapConstIterator &operator++() {
    m_node_ = const_cast<Node_t *>(m_node_)->Forward();
    return *this;
  }

  MapConstIterator &operator++(int) {
    const auto node = m_node_->Forward();
    return MapConstIterator(node);
  }

  MapConstIterator &operator--() {
    m_node_ = m_node_->Backward();
    return *this;
  }

  MapConstIterator &operator--(int) {
    auto node = m_node_->Backward();
    return MapConstIterator(node);
  }

  bool operator==(const MapConstIterator &other) const {
    return m_node_ == other.m_node_;
  }

  bool operator!=(const MapConstIterator &other) const {
    return m_node_ != other.m_node_;
  }

 private:
  const Node_t *m_node_;
};

#endif  // CPP2_S21_CONTAINERS_MAP_MAPITERATOR_H_
