#ifndef LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_GENERATOR_HPP
#define LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_GENERATOR_HPP
#pragma once

#include "reflectedclass.hpp"


namespace metapp {

struct Generator {
  virtual ~Generator() = default;
  std::string m_name;
  std::string name() { return m_name; }
  void name(std::string name) { m_name = std::move(name); }
  virtual void setup() {}
  virtual void generate(clang::ASTContext *ctx, raw_ostream &os,
                        ReflectedClass const &reflectedClass) const = 0;
};

} // namespace metapp

#endif // LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_GENERATOR_HPP
