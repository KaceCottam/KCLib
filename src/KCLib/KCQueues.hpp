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
    friend bool operator==(queue<T, Size>::iterator &lhs,queue<T, Size>::iterator &rhs);
    friend bool operator!=(queue<T, Size>::iterator &lhs,queue<T, Size>::iterator &rhs);
    friend bool operator<(queue<T, Size>::iterator &lhs,queue<T, Size>::iterator &rhs);
    friend bool operator>(queue<T, Size>::iterator &lhs,queue<T, Size>::iterator &rhs);
    friend bool operator<=(queue<T, Size>::iterator &lhs,queue<T, Size>::iterator &rhs);
    friend bool operator>=(queue<T, Size>::iterator &lhs,queue<T, Size>::iterator &rhs);
  };
  queue();
  queue(queue<T, Size> &&other) noexcept;
  queue(queue<T, Size> const &other);
  queue<T, Size> &operator=(queue<T, Size> &&other) noexcept;
  queue<T, Size> &operator=(queue<T, Size> const &other);
  queue(const T &data);
  template <typename... Args>
  queue(const Args &... data);
  size_t size() const;
  bool empty() const;
  void empty(int);
  void enqueue(T const &data);
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

}  // namespace kc