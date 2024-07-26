#pragma once

#ifndef FALLMENTO_H
#define FALLMENTO_H

#include <functional>
#include <optional>

namespace fallmento {

enum class FoState { START, GO, YIELD, STOP };

template <typename Ret, typename User>
class fallroutine {

  public:
    using FoTask = std::function<Ret(fallroutine*, User*)>;

  public:
    fallroutine(FoTask task, User* user_data)
        : __state{FoState::START}, __task{task}, __user_data{user_data} {}

    fallroutine(fallroutine&) = delete;
    fallroutine(fallroutine&&) = delete;

    auto next() -> std::optional<Ret> {

        auto res = __task(this, __user_data);

        return get_state() == FoState::STOP
                   ? std::nullopt
                   : std::make_optional(std::move(res));
    }

    auto has_next() -> bool { return __state != FoState::STOP; }

    auto get_state() -> FoState { return __state; }

    auto set_state(FoState s) -> void { __state = s; }

  private:
    FoState __state;
    FoTask __task;
    User* __user_data;
};

} // namespace fallmento

#endif