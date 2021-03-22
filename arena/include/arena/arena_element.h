#ifndef ARENA_INCLUDE_ARENA_ARENA_ELEMENT_H
#define ARENA_INCLUDE_ARENA_ARENA_ELEMENT_H

namespace shrimp {
namespace arena {

namespace detail {
template <typename T> class ArenaElement {
public:
  T *t;
  ArenaElement<T> *next;

  static ArenaElement<T> *move_front(ArenaElement<T> *&src_list,
                                     ArenaElement<T> *&target_list) {
    if (!src_list) {
      // src list is empty
      return nullptr;
    }
    // remove from src list
    ArenaElement<T> *elem = src_list;
    src_list = src_list->next;
    // add to target list
    elem->next = target_list;
    target_list = elem;

    return elem;
  }
};

} // namespace detail
} // namespace arena
} // namespace shrimp

#endif
