
#ifndef ARENA_INCLUDE_ARENA_I_ARENA_H
#define ARENA_INCLUDE_ARENA_I_ARENA_H

#include <functional>
#include <memory>

namespace shrimp {
namespace arena {

template <typename T>
using unique_ptr = std::unique_ptr<T, std::function<void(T *)>>;

template <typename T> class IArena {
public:
  IArena() = default;
  virtual ~IArena() = default;
  IArena(const IArena &) = delete;
  IArena(IArena &&) = delete;
  IArena &operator=(const IArena &) = delete;
  IArena &operator=(IArena &&) = delete;

  virtual bool initialize(std::size_t size) = 0;
  virtual unique_ptr<T> create() = 0;
};

} // namespace arena
} // namespace shrimp

#endif