#include "tqdm.h"
#include "sol.hpp"
#include <vector>
auto range(const int start, const int finish, const sol::optional<int> _step,
           sol::this_state L) {
  const int step = _step.value_or(1);
  sol::state_view lua(L);
  auto f = [=](lib::tqdm &progressBar, const int previous) -> sol::object {
    unsigned p =
        std::max(0L, std::lround(float(previous - start + step) / step));
    progressBar.progress(p);
    int next = previous + step;
    if (std::min(start, finish) <= next and next <= std::max(start, finish)) {
      return sol::make_object(lua, next);
    } else {
      return sol::lua_nil;
    }
  };
  return std::make_tuple(
      f, lib::tqdm((std::abs(finish - start) + 1) / std::abs(step)),
      start - step);
}

auto ipairs(const std::vector<sol::object> t, sol::this_state L) {
  sol::state_view lua(L);
  auto f = [=](lib::tqdm &progressBar, const int previous) {
    progressBar.progress(previous);
    const int next = previous + 1;
    sol::variadic_results res;
    if (next <= int(t.size())) {
      res.push_back({lua, sol::in_place, next});
      res.push_back({lua, sol::in_place, t[next - 1]});
    } else {
      res.push_back({lua, sol::lua_nil});
    }
    return res;
  };
  return std::make_tuple(f, lib::tqdm(t.size()), 0);
}

extern "C" int luaopen_tqdm(lua_State *L) {
  return sol::stack::call_lua(L, 1, [](sol::this_state L) -> sol::table {
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module.new_usertype<lib::tqdm>(
        "M", sol::constructors<lib::tqdm(unsigned)>(), "progress",
        &lib::tqdm::progress, "theme", &lib::tqdm::theme, "range", &range,
        "ipairs", &ipairs);
    return module["M"];
  });
}
