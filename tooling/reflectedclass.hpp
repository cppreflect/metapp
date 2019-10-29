#ifndef METAREFLECT_REFLECTED_CLASS_HPP
#define METAREFLECT_REFLECTED_CLASS_HPP
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

#endif /* METAREFLECT_REFLECTED_CLASS_HPP */
