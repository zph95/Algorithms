# string_match binary
add_executable(string_match string_match.cpp)

enable_testing()

add_test(
  NAME string_match_test
  COMMAND $<TARGET_FILE:string_match>
  )
