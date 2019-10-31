#ifndef LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_TEMPLATE_GENERATOR_HPP
#define LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_TEMPLATE_GENERATOR_HPP
#pragma once

#include "generator.hpp"

namespace metapp {

struct TemplateGenerator : public Generator {
  void setup() override;

  void generate(ASTContext *ctx, raw_ostream &os,
                ReflectedClass const &reflectedClass) const override;

private:
  std::string m_template;
};

} // namespace metapp

#endif // LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_TEMPLATE_GENERATOR_HPP
