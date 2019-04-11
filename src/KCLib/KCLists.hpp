//@KCLIB_FILE_COMMENT@
#pragma once

#include <KCLib/KCExceptions.hpp>

namespace kc {
struct out_of_range : bad_index {
  enum Range {
    LESS_THAN,
    GREATER_THAN,
    LESS_THAN_OR_EQUAL_TO,
    GREATER_THAN_OR_EQUAL_TO,
    INVALID
  } range;
  out_of_range(Range range, size_t value);
  out_of_range();
};

template <typename T>
class list {
 public:
  struct node {
    T data;
    node *next;
    node *previous;

    static void LinkNodes(node *lhs, node *rhs) noexcept;
    template <typename... Args>
    static void LinkNodes(node *lhs, node *rhs, Args... args) noexcept;

    T &operator*() noexcept;
    T *operator->() noexcept;
  };

  struct iterator {
    node *current_node;
    iterator(node &node) noexcept;
    iterator(node *node) noexcept;
    iterator(const iterator &other) noexcept;
    iterator(iterator &&other) noexcept;
    iterator &operator--();
    iterator operator--(int);
    iterator &operator-=(size_t rhs);
    iterator &operator++();
    iterator operator++(int);
    iterator &operator+=(size_t rhs);
    node *operator->() noexcept;
    T &operator*() noexcept;
  };

  size_t size() const noexcept;
  bool empty() const noexcept;
  iterator begin() const noexcept;
  iterator end() const noexcept;
  T &operator[](size_t index) noexcept;
  T &at(size_t index);
  void push(const T &data);
  template <typename... Args>
  void push(const T &data, const Args &... args);
  void push_back(const T &data);
  template <typename... Args>
  void push_back(const T &data, const Args &... args);
  T pop();
  T pop_back();
  void empty(int) noexcept;
  ~list() noexcept;
  list();
  template <typename... Args>
  explicit list(const Args &... args);
  list(const list<T> &other);
  list(list<T> &&other) noexcept;
  list<T> &operator=(const list<T> &other);
  list<T> &operator=(list<T> &&other) noexcept;

 private:
  size_t length_{0};
  node *header_{nullptr};
};

inline out_of_range::out_of_range(Range const range, size_t const value)
    : bad_index{value}, range{range} {}

inline out_of_range::out_of_range() : bad_index{0}, range{INVALID} {}

template <typename T>
T &list<T>::node::operator*() noexcept {
  return data;
}

template <typename T>
T *list<T>::node::operator->() noexcept {
  return &data;
}

template <typename T>
void list<T>::node::LinkNodes(node *lhs, node *rhs) noexcept {
  lhs->next = rhs;
  rhs->previous = lhs;
}

template <typename T>
template <typename... Args>
void list<T>::node::LinkNodes(node *lhs, node *rhs, Args... args) noexcept {
  LinkNodes(lhs, rhs);
  LinkNodes(rhs, args...);
}

template <typename T>
list<T>::iterator::iterator(node &node) noexcept : iterator{&node} {}

template <typename T>
list<T>::iterator::iterator(node *node) noexcept : current_node{node} {
  if (!current_node) {
    // throw bad_index(1);
  }
}
template <typename T>
list<T>::iterator::iterator(const iterator &other) noexcept
    : current_node{other.current_node} {}

template <typename T>
list<T>::iterator::iterator(iterator &&other) noexcept
    : current_node{other.current_node} {
  other.current_node = nullptr;
}

template <typename T>
auto list<T>::iterator::operator--() -> iterator & {
  if (!current_node) throw out_of_range{};
  current_node = current_node->previous;
  return *this;
}

template <typename T>
auto list<T>::iterator::operator--(int) -> iterator {
  auto temp{*this};
  --*this;
  return temp;
}

template <typename T>
auto list<T>::iterator::operator-=(size_t const rhs) -> iterator & {
  for (size_t i = 0; i < rhs; i++) {
    --*this;
  }
  return *this;
}

template <typename T>
auto list<T>::iterator::operator++() -> iterator & {
  if (!current_node) throw out_of_range{};
  current_node = current_node->next;
  return *this;
}

template <typename T>
auto list<T>::iterator::operator++(int) -> iterator {
  auto temp{*this};
  ++*this;
  return temp;
}

template <typename T>
auto list<T>::iterator::operator+=(size_t const rhs) -> iterator & {
  for (size_t i = 0; i < rhs; i++) {
    ++*this;
  }
  return *this;
}

template <typename T>
auto list<T>::iterator::operator-> () noexcept -> node * {
  return current_node;
}

template <typename T>
auto list<T>::iterator::operator*() noexcept -> T& {
  return **current_node;
}

template <typename T>
size_t list<T>::size() const noexcept {
  return length_;
}

template <typename T>
bool list<T>::empty() const noexcept {
  return size() == 0;
}

template <typename T>
auto list<T>::begin() const noexcept -> iterator {
  return iterator{header_};
}

template <typename T>
auto list<T>::end() const noexcept -> iterator {
  return begin() += (size() - 1);
}

template <typename T>
T &list<T>::operator[](size_t const index) noexcept {
  return (begin() += index)->data;
}

template <typename T>
T &list<T>::at(size_t const index) {
  if (index < 0) throw out_of_range{out_of_range::LESS_THAN, 0};
  if (index >= size())
    throw out_of_range{out_of_range::GREATER_THAN_OR_EQUAL_TO, size()};
  return *this[index];
}

template <typename T>
void list<T>::push(const T &data) {
  auto new_node = new node{data};
  if (!new_node) throw out_of_memory{};
  node::LinkNodes(new_node, begin().current_node);
  header_ = new_node;
  ++length_;
}

template <typename T>
template <typename... Args>
void list<T>::push(const T &data, const Args &... args) {
  push(data);
  push(args...);
}

template <typename T>
void list<T>::push_back(const T &data) {
  if (!header_) return push(data);
  auto new_node = new node{data};
  if (!new_node) throw out_of_memory{};
  node::LinkNodes(end().current_node, new_node);
  ++length_;
}

template <typename T>
template <typename... Args>
void list<T>::push_back(const T &data, const Args &... args) {
  push_back(data);
  push_back(args...);
}

template <typename T>
T list<T>::pop() {
  auto header = begin();
  T data{*header};
  header_ = header->next;
  delete header.current_node;
  --length_;
  return data;
}

// TODO: T[] pop()

template <typename T>
T list<T>::pop_back() {
  auto back = end();
  T data{*back};
  node::LinkNodes(back->previous, nullptr);
  delete (back.current_node);
  --length_;
  return data;
}

// TODO: T[] pop_back()

template <typename T>
void list<T>::empty(const int) noexcept {
  while (!empty()) pop();
}

template <typename T>
list<T>::~list() noexcept {
  empty(0);
}

template <typename T>
list<T>::list() = default;

template <typename T>
template <typename... Args>
list<T>::list(const Args &... data) {
  push(data...);
}

template <typename T>
list<T>::list(const list<T> &other) {
  auto other_traversal = other.begin();
  for (auto &i : other) {
    push(*i);
  }
}

template <typename T>
list<T>::list(list<T> &&other) noexcept
    : length_{other.length_}, header_{other.header_} {
  other.length_ = 0;
  other.header_ = nullptr;
}

template <typename T>
list<T> &list<T>::operator=(const list<T> &other) {
  if (this != &other) {
    empty(0);
    auto other_traversal = other.begin();
    for (auto &i : other) {
      push(*i);
    }
  }
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list<T> &&other) noexcept {
  if (this != &other) {
    empty(0);
    length_ = other.length_;
    header_ = other.header_;
    other.length_ = 0;
    other.header_ = nullptr;
  }
  return *this;
}
}  // namespace kc