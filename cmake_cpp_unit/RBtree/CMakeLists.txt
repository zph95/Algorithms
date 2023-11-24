# RBtree binary
add_executable(rbtree rbtree.cpp)

enable_testing()

add_test(
  NAME rbtree_test
  COMMAND $<TARGET_FILE:rbtree>
  )
