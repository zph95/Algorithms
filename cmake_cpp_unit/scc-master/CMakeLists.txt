# scc_master binary
add_executable(scc_test scc_src.cpp)

enable_testing()

add_test(
  NAME scc_unit_test
  COMMAND $<TARGET_FILE:scc_test>
)
