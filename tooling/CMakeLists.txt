set(LLVM_LINK_COMPONENTS Support)

add_clang_executable(mpp 
  annotations.hpp 
  classfinder.hpp
  generator.hpp
  generator_store.hpp
  init_generators.cpp
  init_generators.hpp
  reflect.cpp
  reflectedclass.cpp
  reflectedclass.hpp
  runtime_reflection_generator.cpp
  runtime_reflection_generator.hpp
  utils.cpp
  utils.hpp
)

target_link_libraries(mpp PRIVATE clangTooling clangBasic clangASTMatchers)
