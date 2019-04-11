//@KCLIB_FILE_COMMENT
#pragma once

#include <initializer_list>
#include <stdexcept>

namespace kc {
template <typename T, int Size>
class queue final {
 public:
  struct iterator {
    T *current_data;
    iterator &operator--();
    iterator operator--(int);
    iterator &operator-=(size_t number);
    iterator &operator++();
    iterator operator++(int);
    iterator &operator+=(size_t number);
    T *operator->();
    T &operator*();
  };
  queue();
  queue(queue<T, Size> &&other) noexcept;
  queue(const queue<T, Size> &other);
  queue<T, Size> &operator=(queue<T, Size> &&other) noexcept;
  queue<T, Size> &operator=(const queue<T, Size> &other);
  template <typename... Args>
  queue(const Args &... data);
  size_t size() const;
  bool empty() const;
  void empty(int);
  void enqueue(const T &data);
  template <typename... Args>
  void enqueue(const T &data, const Args &... args);
  T dequeue();
  T &peek() const;

  ~queue();

 private:
  T data_[Size] {nullptr};
  size_t current_size_ {0U};
};

template <typename T, int Size>
auto queue<T, Size>::iterator::operator--() -> iterator & {
  --current_data;
  return *this;
}

template <typename T, int Size>
auto queue<T, Size>::iterator::operator--(int) -> iterator {
  auto temp{*this};
  --*this;
  return temp;
}

template <typename T, int Size>
auto queue<T, Size>::iterator::operator-=(size_t const number) -> iterator & {
  for (size_t i = 0; i < number; i++) {
    --*this;
  }
  return *this;
}

template <typename T, int Size>
auto queue<T, Size>::iterator::operator++() -> iterator & {
  ++current_data;
  return *this;
}

template <typename T, int Size>
auto queue<T, Size>::iterator::operator++(int) -> iterator {
  auto temp{*this};
  ++*this;
  return temp;
}

template <typename T, int Size>
auto queue<T, Size>::iterator::operator+=(size_t const number) -> iterator & {
  for (size_t i = 0; i < number; i++) {
    ++*this;
  }
  return *this;
}

template <typename T, int Size>
T *queue<T, Size>::iterator::operator->() {
  return current_data;
}

template <typename T, int Size>
T &queue<T, Size>::iterator::operator*() {
  return *current_data;
}

template <typename T, int Size>
bool operator==(typename queue<T, Size>::iterator &lhs,typename  queue<T, Size>::iterator &rhs) {
  return lhs.current_data == rhs.current_data;
}
template <typename T, int Size>
bool operator!=(typename queue<T, Size>::iterator &lhs, typename queue<T, Size>::iterator &rhs) {
  return !(lhs == rhs);
}
template <typename T, int Size>
bool operator<(typename queue<T, Size>::iterator &lhs, typename queue<T, Size>::iterator &rhs) {
  return lhs.current_data < rhs.current_data;
}
template <typename T, int Size>
bool operator>(typename queue<T, Size>::iterator &lhs, typename queue<T, Size>::iterator &rhs) {
  return lhs.current_data > rhs.current_data;
}
template <typename T, int Size>
bool operator<=(typename queue<T, Size>::iterator &lhs, typename queue<T, Size>::iterator &rhs) {
  return !(lhs > rhs);
}
template <typename T, int Size>
bool operator>=(typename queue<T, Size>::iterator &lhs, typename queue<T, Size>::iterator &rhs) {
  return !(lhs < rhs);
}

template <typename T, int Size>
queue<T, Size>::queue() = default;

template <typename T, int Size>
queue<T, Size>::queue(queue<T, Size> &&other) noexcept
    : current_data_{other._data_}, current_size_{other.current_size_} {
  other.current_size_ = 0;
  other.data_ = nullptr;
}

template <typename T, int Size>
queue<T, Size>::queue(const queue<T, Size> &other) {
  for (auto i : other) {
    enqueue(*i);
  }
}

template <typename T, int Size>
auto queue<T, Size>::operator=(queue<T, Size> &&other) noexcept -> queue & {
  if(this != &other)
  {
    empty(0);
    data_ = std::move(other.data_);
    current_size_ = std::move(other.current_size_);
  }
}

template <typename T, int Size>
auto queue<T, Size>::operator=(const queue<T, Size> &other) -> queue & {
  if(this != &other)
  {
    empty(0);
    for (auto i : other) {
      enqueue(*i);
    }
  }
}

template <typename T, int Size>
template <typename... Args>
queue<T, Size>::queue(const Args &... data) {
  enqueue(data...);
}

template <typename T, int Size>
size_t queue<T, Size>::size() const {
  return current_size_;
}

template <typename T, int Size>
bool queue<T, Size>::empty() const {
  return size() == 0;
}

template <typename T, int Size>
void queue<T, Size>::empty(int) {
  while (!empty()) {
    dequeue();
  }
}

template <typename T, int Size>
void queue<T, Size>::enqueue(const T &data) {
  data_[current_size_++] = data;
}

template <typename T, int Size>
template <typename... Args>
void queue<T, Size>::enqueue(const T &data, const Args &... args)
{
  enqueue(data);
  enqueue(args...);
}

template <typename T, int Size>
T queue<T, Size>::dequeue() {
  return std::move(data_[--current_size_]);
}

template <typename T, int Size>
T &queue<T, Size>::peek() const {
  return data_[current_size_ - 1]);
}

template <typename T, int Size>
queue<T, Size>::~queue() {
  empty(0);
}

}  // namespace kc