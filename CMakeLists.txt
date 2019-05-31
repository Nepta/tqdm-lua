cmake_minimum_required(VERSION 3.12)
project(tqdm)

set(CMAKE_CXX_STANDARD 17)

find_package(Lua REQUIRED)

include_directories(${LUA_INCLUDE_DIR})
add_library(tqdm SHARED library.cpp tqdm.h)
target_link_libraries(tqdm ${LUA_LIBRARIES})
set_target_properties(tqdm PROPERTIES PREFIX "")
target_compile_options(tqdm PRIVATE -Wall -Wextra)
install(TARGETS tqdm DESTINATION "${LIBDIR}")