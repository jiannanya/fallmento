// not support by msvc compiler
#pragma once
#ifndef FALLMENTO_H
#define FALLMENTO_H

#include <functional>
#include <optional>

#define _fo_line3(name, line) _fo_##name##line
#define _fo_line2(name, line) _fo_line3(name, line)
#define _fo_line(name) _fo_line2(name, __LINE__)

#define TO_TAG(tag) _fo_line(tag)

#define FO_BEGIN(fo)                                                           \
    if ((fo)->__tag == nullptr) {                                              \
        goto TO_TAG(tag);                                                      \
    } else {                                                                   \
        goto*(fo->__tag);                                                      \
    }                                                                          \
    TO_TAG(tag) :

#define FO_YIELD(fo, value)                                                    \
    (fo)->__tag = &&TO_TAG(tag);                                               \
    (fo)->set_state(FoState::YIELD);                                           \
    return (value);                                                            \
    TO_TAG(tag) :

#define FO_RETURN(fo, value)                                                   \
    (fo)->set_state(FoState::STOP);                                            \
    return (value);

namespace fallmento {

enum class FoState { START, GO, YIELD, STOP };

template <typename Ret, typename User>
class fallroutine {

  public:
    using FoTask = std::function<Ret(fallroutine*, User*)>;

  public:
    fallroutine(FoTask task, User* user_data)
        : __state{FoState::START}, __task{task}, __user_data{user_data},
          __tag{nullptr} {}

    fallroutine(fallroutine&) = delete;
    fallroutine(fallroutine&&) = delete;

    auto next() -> std::optional<Ret> {

        if (get_state() == FoState::START) {
            set_state(FoState::GO);
        }

        if (get_state() == FoState::STOP) {
            return std::nullopt;
        }
        auto res = __task(this, __user_data);

        return std::make_optional(std::move(res));
    }

    auto has_next() -> bool { return __state != FoState::STOP; }

    auto get_state() -> FoState { return __state; }

    auto set_state(FoState s) -> void { __state = s; }

  public:
    void* __tag;

  private:
    FoState __state;
    FoTask __task;
    User* __user_data;
};

} // namespace fallmento

#endif