
#ifndef ARENA_INCLUDE_ARENA_ARENA_H
#define ARENA_INCLUDE_ARENA_ARENA_H

#include <arena/arena_element.h>
#include <arena/i_arena.h>
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
    list_elements_ =
        std::vector<detail::ArenaElement<T>>(size, {nullptr, nullptr});
    if (!initialize_list_pointers(size)) {
      return false;
    }
    // all are free
    free_list_ = &list_elements_[0];
    in_use_list_ = nullptr;
    initialized_ = true;

    // initialize arena deleter
    reusage_deleter_ = [this](T *t) {
      auto arena_element = detail::ArenaElement<T>::move_front(
          this->in_use_list_, this->free_list_);
      arena_element->t = t;
    };

    return true;
  }

  arena_ptr<T> create() override {
    auto arena_element =
        detail::ArenaElement<T>::move_front(free_list_, in_use_list_);
    if (!arena_element) {
      return {nullptr, reusage_deleter_};
    }
    return {arena_element->t, reusage_deleter_};
  }

private:
  bool initialize_list_pointers(std::size_t size) {
    // all but last
    for (std::size_t i = 0; i < size - 1; i++) {
      list_elements_[i].t = &memory_[i];
      list_elements_[i].next = &list_elements_[i + 1];
    }
    // last
    list_elements_[size - 1].t = &memory_[size - 1];
    list_elements_[size - 1].next = nullptr;

    return true;
  }

  bool initialized_{false};
  std::vector<T> memory_; // actual elements are stored here
  std::vector<detail::ArenaElement<T>>
      list_elements_; // actual elements are stored here
  detail::ArenaElement<T> *free_list_;
  detail::ArenaElement<T> *in_use_list_;
  std::function<void(T *t)> reusage_deleter_;
};

} // namespace arena
} // namespace shrimp

#endif