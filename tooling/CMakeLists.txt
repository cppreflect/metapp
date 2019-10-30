set(LLVM_LINK_COMPONENTS Support)

add_clang_executable(mpp 
  annotations.hpp 
  classfinder.hpp
  command_line.hpp
  generator.hpp
  generator_store.hpp
  init_generators.cpp
  init_generators.hpp
  reflect.cpp
  reflectedclass.cpp
  reflectedclass.hpp
  runtime_reflection_generator.cpp
  runtime_reflection_generator.hpp
  template_generator.cpp
  template_generator.hpp
  utils.cpp
  utils.hpp
)

target_compile_options(mpp PRIVATE -fexceptions)
target_link_libraries(mpp PRIVATE templatingLib clangTooling clangBasic clangASTMatchers)
