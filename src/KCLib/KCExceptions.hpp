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

failure::failure() : failure{"[KCLib] failure encountered."} {}
failure::failure(const char* message)
    : logic_error{"[KCLib] failure encountered."}, message{message} {}

out_of_memory::out_of_memory() : failure{"Out of memory"} {}

bad_index::bad_index(const size_t index) : failure{"Accessed a bad index."}, index{index} {}
}  // namespace kc
