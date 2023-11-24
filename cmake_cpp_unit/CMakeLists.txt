cmake_minimum_required(VERSION 3.0.0)
project(cmake_unit_cpp VERSION 0.1.0 LANGUAGES C CXX)


add_executable(cmake_unit_cpp main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(CTest)
add_subdirectory(string_match)
add_subdirectory(scc-master)
add_subdirectory(RBtree)
enable_testing()