#ifndef LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_REFLECTEDCLASS_HPP
#define LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_REFLECTEDCLASS_HPP
#pragma once

#include "annotations.hpp"
#include "utils.hpp"


class ReflectedClass {
public:
  ReflectedClass(CXXRecordDecl const *rec)
      : m_record(rec) {}

  /* ===--------------------------------------------------=== */
  /* Public API                                               */
  /* ===--------------------------------------------------=== */

  void AddField(FieldDecl const *field) { m_fields.push_back(field); }

  void AddFunction(FunctionDecl const *function) {
    m_functions.push_back(function);
  }

  CXXRecordDecl const *const m_record;
  std::vector<FieldDecl const *> m_fields;
  std::vector<FunctionDecl const *> m_functions;
};

#endif // LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_REFLECTEDCLASS_HPP
