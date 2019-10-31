#ifndef LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_REFLECTEDCLASS_HPP
#define LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_REFLECTEDCLASS_HPP
#pragma once

#include "annotations.hpp"
#include "utils.hpp"


class ReflectedClass {
public:
  ReflectedClass(clang::CXXRecordDecl const *rec)
      : m_record(rec) {}

  /* ===--------------------------------------------------=== */
  /* Public API                                               */
  /* ===--------------------------------------------------=== */

  void AddField(clang::FieldDecl const *field) { m_fields.push_back(field); }

  void AddFunction(clang::FunctionDecl const *function) {
    m_functions.push_back(function);
  }

  clang::CXXRecordDecl const *const m_record;
  std::vector<clang::FieldDecl const *> m_fields;
  std::vector<clang::FunctionDecl const *> m_functions;
};

#endif // LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_REFLECTEDCLASS_HPP
