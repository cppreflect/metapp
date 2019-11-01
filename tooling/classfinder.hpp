#ifndef LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_CLASSFINDER_HPP
#define LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_CLASSFINDER_HPP
#pragma once

#include "generator.hpp"
#include "generator_store.hpp"
#include "reflectedclass.hpp"
#include "utils.hpp"


class ClassFinder : public MatchFinder::MatchCallback {
public:
  // ClassFinder() = default;
  ClassFinder(std::string fileName,
              std::shared_ptr<metapp::GeneratorStore> generators)
      : m_fileName{std::move(fileName)}
      , m_generators{std::move(generators)} {}

  virtual void run(MatchFinder::MatchResult const &result) override {
    m_context = result.Context;
    m_sourceman = result.SourceManager;

    clang::CXXRecordDecl const *record =
        result.Nodes.getNodeAs<clang::CXXRecordDecl>("id");
    if (record)
      return FoundRecord(record);

    clang::FieldDecl const *field =
        result.Nodes.getNodeAs<clang::FieldDecl>("id");
    if (field)
      return FoundField(field);

    clang::FunctionDecl const *function =
        result.Nodes.getNodeAs<clang::FunctionDecl>("id");
    if (function)
      return FoundFunction(function);
  }

  virtual void onStartOfTranslationUnit() override {}

  virtual void onEndOfTranslationUnit() override {
    /* For stdout output. */
    /* raw_fd_ostream os(1, false); */
    std::error_code ec;
    raw_fd_ostream os(m_fileName, ec);
    assert(!ec && "error opening file");
    for (auto &ref : m_classes) {
      // ref.Generate(m_context, os);
      try {
        auto generator = m_generators->mockGet("some_generator");
        generator->generate(m_context, os, ref);
      } catch (const std::runtime_error &err) {
        llvm::errs() << err.what() << '\n';
      }
    }
  }


protected:
  void FoundRecord(clang::CXXRecordDecl const *record) {
    if (m_fileName.empty()) {
      m_fileName = m_sourceman->getFilename(record->getLocation());
      m_fileName.erase(m_fileName.end() - 4, m_fileName.end());
      m_fileName.append(".generated.hxx");
    }

    clang::DeclContext const *decl_context =
        record->getEnclosingNamespaceContext();
    clang::NamespaceDecl const *namesp = nullptr;

    if (decl_context->isNamespace()) {
      namesp = clang::cast<clang::NamespaceDecl>(decl_context);
    }

    m_classes.emplace_back(ReflectedClass(namesp, record));
  }

  void FoundField(clang::FieldDecl const *field) {
    m_classes.back().AddField(field);
  }

  void FoundFunction(clang::FunctionDecl const *function) {
    m_classes.back().AddFunction(function);
  }

protected:
  clang::ASTContext *m_context;
  clang::SourceManager *m_sourceman;
  std::vector<ReflectedClass> m_classes;
  std::string m_fileName;
  std::shared_ptr<metapp::GeneratorStore> m_generators;
};

#endif // LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_CLASSFINDER_HPP
