#include <stdexcept>
#include <cstddef>
namespace kc {

struct failure : std::logic_error {
  failure();
  failure(const char* message);
  const char* message;
};

struct out_of_memory : failure {
  out_of_memory();
};

struct bad_index : failure {
  bad_index(const size_t index);
  const size_t index;
};

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

failure::failure() : failure{"[KCLib] failure encountered."} {}
failure::failure(const char* message)
    : logic_error{"[KCLib] failure encountered."}, message{message} {}

out_of_memory::out_of_memory() : failure{"Out of memory"} {}

bad_index::bad_index(const size_t index)
    : failure{"Accessed a bad index."}, index{index} {}

out_of_range::out_of_range(Range const range, size_t const value)
    : bad_index{value}, range{range} {}

out_of_range::out_of_range() : bad_index{0}, range{INVALID} {}

}  // namespace kc
