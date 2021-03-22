
#ifndef ARENA_INCLUDE_ARENA_ARENA_H
#define ARENA_INCLUDE_ARENA_ARENA_H

#include <arena/i_arena.h>
#include <list>
#include <type_traits>
#include <vector>

namespace shrimp {
namespace arena {

template <typename T> class Arena : public IArena<T> {
  static_assert(std::is_default_constructible<T>::value,
                "Arena type is not default constructable.");

public:
  Arena() = default;
  ~Arena() = default;
  Arena(const Arena &) = delete;
  Arena(Arena &&) = default;
  Arena &operator=(const Arena &) = delete;
  Arena &operator=(Arena &&) = delete;

  bool initialize(std::size_t size) override {
    memory_ = std::vector<T>(size, T{});
    // all are free
    for (std::size_t i = 0; i < size; i++) {
      free_list_.push_back(&memory_[i]);
    }

    // initialize Arena deleter
    reusage_deleter_ = [this](T *t) {
      if (t) {
        free_list_.splice(free_list_.end(), in_use_list_, in_use_list_.begin());
        free_list_.back() = t;
      }
    };

    initialized_ = true;

    return true;
  }

  arena_ptr<T> create() override {
    if (free_list_.empty()) {
      return {nullptr, reusage_deleter_};
    }
    in_use_list_.splice(in_use_list_.end(), free_list_, free_list_.begin());
    return {in_use_list_.back(), reusage_deleter_};
  }

private:
  bool initialized_{false};
  std::vector<T> memory_; // actual elements are stored here
  std::list<T *> free_list_{};
  std::list<T *> in_use_list_{};
  std::function<void(T *t)> reusage_deleter_;
};

} // namespace arena
} // namespace shrimp

#endif