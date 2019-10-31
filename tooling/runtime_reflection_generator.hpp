#ifndef LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_RUNTIME_REFLECTION_GENERATOR_HPP
#define LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_RUNTIME_REFLECTION_GENERATOR_HPP
#pragma once

#include "generator.hpp"
#include "reflectedclass.hpp"

namespace metapp {

struct RuntimeReflectionGenerator : public Generator {

  void setup() override { name("RuntimeReflectionGenerator"); }

  void generate(ASTContext *ctx, raw_ostream &os,
                ReflectedClass const &reflectedClass) const override;
};

} // namespace metapp

#endif // LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_RUNTIME_REFLECTION_GENERATOR_HPP
