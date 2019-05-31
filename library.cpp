#include "tqdm.h"
#include "sol.hpp"
extern "C"
int luaopen_tqdm(lua_State* L) {
	return sol::stack::call_lua(L, 1, [](sol::this_state L) -> sol::table {
		sol::state_view lua(L);
		sol::table module = lua.create_table();
		module.new_usertype<lib::tqdm>("M",
				sol::constructors<lib::tqdm(unsigned)>(),
				"progress", &lib::tqdm::progress,
				"theme", &lib::tqdm::theme);
		return module["M"];
	});
}
