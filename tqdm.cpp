#include "tqdm.h"
#include "sol.hpp"
auto range(const int start, const int finish, const sol::optional<int> _step, sol::this_state L) {
  /*
   * function(start, finish)
      local f = function(progressBar, previous)
         progressBar:progress(previous)
         if previous + 1 <= finish then
            return previous + 1
         else
            return nil
         end
      end
      return f, tqdm_.new(finish - start + 1), start - 1
   end
   */
  const int step = _step.value_or(1);
  sol::state_view lua(L);
  auto f = [=](lib::tqdm &progressBar, const int previous) -> sol::object {
    int p = (std::lround(float(previous - start + step)/step));
    progressBar.progress(p);
    int next = previous + step;
    if (std::min(start, finish) <= next and next <= std::max(start, finish)) {
      return sol::make_object(lua, previous + step);
    } else {
      return sol::lua_nil;
    }
  };
  std::cout << "N : " << (std::abs(finish - start) + 1) / std::abs(step) << std::endl;
  return std::make_tuple(f, lib::tqdm((std::abs(finish - start) + 1) / std::abs(step)), start - step);
}

extern "C" int luaopen_tqdm(lua_State *L) {
  return sol::stack::call_lua(L, 1, [](sol::this_state L) -> sol::table {
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module.new_usertype<lib::tqdm>(
        "M", sol::constructors<lib::tqdm(unsigned)>(), "progress",
        &lib::tqdm::progress, "theme", &lib::tqdm::theme, "range", &range);
    return module["M"];
  });
}
