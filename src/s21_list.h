#ifndef CPP2_S21_CONTAINERS_S21_LIST_H_
#define CPP2_S21_CONTAINERS_S21_LIST_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator;

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;

  list() : size_(0) { head_ = tail_ = end_ = new Node(value_type()); }

  list(size_type n) {
    size_ = 0;
    head_ = tail_ = end_ = new Node(value_type());
    for (size_type i = 0; i < n; ++i) push_back(value_type());
  }

  list(std::initializer_list<value_type> const& items) : size_(0) {
    head_ = tail_ = end_ = new Node(value_type());
    for (auto it = items.begin(); it != items.end(); ++it) {
      push_back(*it);
    }
  }

  ~list() { RemoveList(); }

  list(const list& l) : list() {
    for (auto it = l.begin(); it != l.end(); ++it) {
      push_back(*it);
    }
  }

  list& operator=(const list& l) {
    list copy(l);
    swap(this, copy);
    return *this;
  }

  list(list&& l) : list() { swap(l); }

  list& operator=(list&& l) {
    if (this != &l) {
      clear();
      swap(l);
    }
    return *this;
  }

  void swap(list& other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(end_, other.end_);
    std::swap(size_, other.size_);
  }

  const_reference front() const { return head_->data_; }

  const_reference back() const { return tail_->data_; }

  iterator begin() { return iterator(head_); }

  iterator end() { return iterator(end_); }

  iterator begin() const { return iterator(head_); }

  iterator end() const { return iterator(end_); }

  bool empty() const { return size_ == 0; }

  size_type size() { return size_; }

  size_type max_size() {
    return (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
  }

  void clear() {
    while (!empty()) {
      pop_back();
    }
  }

  iterator insert(iterator pos, const_reference value) {
    Node* new_node = new Node(value);

    new_node->next_ = pos.ptr;
    new_node->prev_ = pos.ptr->prev_;
    if (pos == begin())
      head_ = new_node;
    else
      pos.ptr->prev_->next_ = new_node;

    pos.ptr->prev_ = new_node;

    if (pos == end()) tail_ = new_node;
    ++size_;
    return iterator(new_node);
  }

  void erase(iterator pos) {
    if (!empty() && pos != end_) {
      if (pos == begin())
        head_ = pos.ptr->next_;
      else
        pos.ptr->prev_->next_ = pos.ptr->next_;
      if (pos == iterator(tail_)) tail_ = pos.ptr->prev_;
      pos.ptr->next_->prev_ = pos.ptr->prev_;
      delete pos.ptr;
      --size_;
    }
  }

  void pop_back() {
    if (empty())
      throw std::out_of_range("list::pop_back() called with empty list");
    Node* last_node = tail_;
    if (size_ == 1) {
      end_->prev_ = nullptr;
      head_ = tail_ = end_;
    } else if (size_ == 2) {
      tail_ = head_;
      head_->next_ = end_;
      end_->prev_ = head_;
    } else {
      tail_ = tail_->prev_;
      tail_->next_ = end_;
      end_->prev_ = tail_;
    }
    delete last_node;
    --size_;
  }

  void push_back(const_reference value) {
    Node* tmp_node = new Node(value);

    if (size_ == 0) {
      head_ = tail_ = tmp_node;
    } else if (size_ == 1) {
      tail_ = tmp_node;
      head_->next_ = tail_;
      tail_->prev_ = head_;
    } else {
      tail_->next_ = tmp_node;
      tmp_node->prev_ = tail_;
      tail_ = tmp_node;
    }
    end_->prev_ = tail_;
    tail_->next_ = end_;
    ++size_;
    end_->data_ = size_;
  }

  void push_front(const_reference value) {
    Node* tmp_node = new Node(value);
    if (size_ == 0) {
      head_ = tail_ = tmp_node;
      end_->prev_ = tail_;
      tail_->next_ = end_;
    } else if (size_ == 1) {
      head_ = tmp_node;
      head_->next_ = tail_;
      tail_->prev_ = head_;
    } else {
      head_->prev_ = tmp_node;
      tmp_node->next_ = head_;
      head_ = tmp_node;
    }
    ++size_;
    end_->data_ = size_;
  }

  void pop_front() {
    if (empty())
      throw std::out_of_range("list::pop_front() called with empty list");
    Node* first_node = head_;
    if (size_ == 1) {
      end_->prev_ = nullptr;
      head_ = tail_ = end_;
    } else if (size_ == 2) {
      head_ = tail_;
      head_->prev_ = nullptr;
    } else {
      head_ = head_->next_;
      head_->prev_ = nullptr;
    }
    delete first_node;
    --size_;
  }

  void merge(list& other) {
    iterator this_it = begin();
    iterator other_it = other.begin();
    while (other_it != other.end()) {
      if (*this_it <= *other_it && this_it != end()) {
        ++this_it;
      } else if (*this_it > *other_it || this_it == end()) {
        insert(this_it, *other_it);
        ++other_it;
      }
    }
  }

  void splice(const_iterator pos, list& other) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert(pos, *it);
    }
    other.clear();
  }

  void reverse() {
    Node* head_node = head_;
    Node* tail_node = tail_;
    size_type half = size_ / 2;
    for (size_type step = 0; step < half; ++step) {
      std::swap(head_node->data_, tail_node->data_);
      head_node = head_node->next_;
      tail_node = tail_node->prev_;
    }
  }

  void unique() {
    for (auto it = ++(begin()); it != end() && !empty(); ++it) {
      if (it.ptr->data_ == it.ptr->prev_->data_) {
        iterator on_delete = iterator(it.ptr->prev_);
        erase(on_delete);
      }
    }
  }

  void sort() { sorting(); }

  void sorting() {
    for (auto current = ++begin(); current != end() && !empty(); ++current) {
      if (current.ptr->data_ < current.ptr->prev_->data_) {
        std::swap(current.ptr->data_, current.ptr->prev_->data_);
        sorting();
      }
    }
  }

 private:
  struct Node {
    Node* next_;
    Node* prev_;
    value_type data_;

    Node(value_type value) : next_(nullptr), prev_(nullptr), data_(value) {}
  };

  Node* head_;
  Node* tail_;
  Node* end_;
  size_type size_;

  void RemoveList() {
    clear();
    delete head_;
  }

  friend ListIterator<T>;
};

template <typename T>
class ListIterator {
 public:
  using reference = T&;
  using value_type = T;
  ListIterator() : ptr(nullptr){};

  ListIterator(typename list<T>::Node* node_ptr) : ptr(node_ptr){};

  reference operator*() {
    if (!ptr) throw std::invalid_argument("It`s empty iterator!");
    return ptr->data_;
  }

  ListIterator& operator++() {
    ptr = ptr->next_;
    return *this;
  }

  ListIterator& operator--() {
    ptr = ptr->prev_;
    return *this;
  }

  ListIterator operator++(int) {
    ListIterator it(*this);
    ++*this;
    return it;
  }

  ListIterator operator--(int) {
    ListIterator it(*this);
    --*this;
    return it;
  }

  bool operator==(ListIterator other) { return this->ptr == other.ptr; }

  bool operator!=(ListIterator other) { return this->ptr != other.ptr; }

 private:
  typename list<T>::Node* ptr;
  friend list<T>;
};

template <typename T>
class ListConstIterator : public ListIterator<T> {
 public:
  using reference = T&;
  using value_type = T;

  ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
  const reference operator*() { return ListIterator<T>::operator*(); }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_H_