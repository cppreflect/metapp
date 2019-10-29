#pragma once

#include "reflectedclass.hpp"


namespace metapp {

struct Generator {
  std::string m_name;
  std::string name() { return m_name; }
  void name(std::string name) { m_name = std::move(name); }
  virtual void setup() {}
  virtual void generate(ASTContext *ctx, raw_ostream &os,
                        ReflectedClass const &reflectedClass) const = 0;
};

} // namespace metapp
