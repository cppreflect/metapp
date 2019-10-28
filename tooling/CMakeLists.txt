set(LLVM_LINK_COMPONENTS Support)

add_clang_executable(mpp 
  reflect.cpp
  reflectedclass.cpp
  annotations.hpp 
  classfinder.hpp
  reflectedclass.hpp
  utils.hpp
  utils.cpp)

target_link_libraries(mpp PRIVATE clangTooling clangBasic clangASTMatchers)
