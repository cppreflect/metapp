#ifndef LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_FUNCTIONGENERATOR_HPP
#define LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_FUNCTIONGENERATOR_HPP
#pragma once

#include "annotations.hpp"
#include "utils.hpp"

/* ========================================================================= */
/* Function Generator                                                        */
/* ========================================================================= */
struct FunctionGenerator {
  clang::ASTContext *const ctx;
  SmallString<64> funcName;
  SmallString<64> typeName;
  raw_svector_ostream funcNameOs{funcName};
  raw_svector_ostream TypeNameOs{typeName};
  StringRef const type;
  StringRef const fieldPrefix;

  explicit FunctionGenerator(clang::ASTContext *context, StringRef const &parentType,
                             StringRef const &prefix)
      : ctx(context)
      , type(parentType)
      , fieldPrefix(prefix) {}

  void Generate(unsigned i, clang::FunctionDecl const *func,
                FunctionAnnotations &annotations, raw_ostream &os) {
    funcName.clear();
    func->printName(funcNameOs);

    os << "\n/* Function " << (i + 1) << "*/\n";
    GenerateReturnType(i, func, annotations, os);
    GenerateArguments(i, func, annotations, os);
    if (func->isCXXClassMember())
      annotations.memberFunc = true;

    auto prefix = [&]() -> raw_ostream & {
      return os << fieldPrefix << "[" << i << "]";
    };
    prefix() << ".m_returnType = &functionRet" << i << ";\n";
    prefix() << ".m_parameters = &functionParameters" << i << "[0];\n";
    prefix() << ".m_parametersEnd = &functionParameters" << i << "["
             << func->getNumParams() << "];\n";
    prefix() << ".m_flags = " << annotations.Flags() << ";\n";
    prefix() << ".m_name = \"" << funcName << "\";\n";
    /* prefix() << ".m_pointer = */
  }

  void GenerateReturnType(unsigned i, clang::FunctionDecl const *func,
                          FunctionAnnotations &annotations, raw_ostream &os) {
    typeName.clear();
    GetRealTypeName(ctx, func->getReturnType(), TypeNameOs);

    /* TODO: used llvm::Type::isSized() instead. */
    SmallString<64> retSize;
    raw_svector_ostream retOstream(retSize);
    if (typeName == "void")
      retOstream << "0";
    else
      retOstream << "sizeof(" << typeName << ")";

    os << "static FunctionReturn functionRet" << i << ";\n";
    /* os << "functionRet" << i << ".m_type = TypeResolver<" << typeName <<
     * ">::Get();\n"; */
    os << "functionRet" << i << ".m_type = GetType<" << typeName << ">();\n";
    os << "functionRet" << i << ".m_flags = 0/*TODO*/;\n";
    os << "functionRet" << i << ".m_serializedWidth = " << retSize << " * 8;\n";
    os << "functionRet" << i
       << ".m_qualifier = " << GenerateQualifier(ctx, func->getReturnType())
       << ";\n";
  }

  void GenerateArguments(unsigned index, clang::FunctionDecl const *func,
                         FunctionAnnotations &annotations, raw_ostream &os) {
    SmallString<64> paramName;
    raw_svector_ostream paramNameOs(paramName);
    unsigned numParams = std::max(func->getNumParams(), 1u);

    os << "static FunctionParameter functionParameters" << index << "["
       << numParams << "];\n";

    for (int i = 0, n = func->getNumParams(); i < n; ++i) {
      clang::ParmVarDecl const *param = func->getParamDecl(i);
      assert(!param->isTemplated() && "templates are unsupported");
      assert(!param->isTemplateParameter() && "templates are unsupported");
      typeName.clear();
      paramName.clear();
      GetRealTypeName(ctx, param->getOriginalType(), TypeNameOs);
      param->printName(paramNameOs);
      auto prefix = [&]() -> raw_ostream & {
        return os << "functionParameters" << index << "[" << i << "]";
      };

      /* prefix() << ".m_type = TypeResolver<" << typeName << ">::Get();\n"; */
      prefix() << ".m_type = GetType<" << typeName << ">();\n";
      prefix() << ".m_flags = 0/*TODO*/;\n";
      prefix() << ".m_serializedWidth = sizeof(" << typeName << ") * 8;\n";
      prefix() << ".m_qualifier = "
               << GenerateQualifier(ctx, param->getOriginalType()) << ";\n";
      prefix() << ".m_name = \"" << paramName << "\";\n";
    }
  }
};

#endif // LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_FUNCTIONGENERATOR_HPP
