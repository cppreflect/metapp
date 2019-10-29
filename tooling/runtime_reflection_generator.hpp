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
