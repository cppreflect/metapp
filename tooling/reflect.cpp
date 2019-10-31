#include <stdio.h>

#include "annotations.hpp"
#include "classfinder.hpp"
#include "generator_store.hpp"
#include "init_generators.hpp"
#include "utils.hpp"

llvm::cl::OptionCategory g_ToolCategory("Metapp options");
static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static llvm::cl::opt<std::string>
    outputOption("output", llvm::cl::cat{g_ToolCategory},
                 llvm::cl::desc{"Set the output file name"},
                 llvm::cl::value_desc{"filename"});
static llvm::cl::alias outputAlias("o", llvm::cl::cat{g_ToolCategory},
                                   llvm::cl::desc{"Alias for output"},
                                   llvm::cl::value_desc{"filename"},
                                   llvm::cl::aliasopt{outputOption});

int main(int argc, const char **argv) {
  /* Parse command-line options. */
  CommonOptionsParser optionsParser(argc, argv, g_ToolCategory);
  if (optionsParser.getSourcePathList().size() > 1) {
    llvm::errs()
        << "More than one input file is currently not supported. Exiting.\n";
    return 1;
  }
  ClangTool tool(optionsParser.getCompilations(),
                 optionsParser.getSourcePathList());

#if 0
    auto &db = optionsParser.getCompilations();
    for (auto &cmd : db.getAllCompileCommands()) {
        printf("CommandLine:");
        for (auto &opt : cmd.CommandLine)
            printf(" %s", opt.c_str());
        printf("\n");
        printf("File: %s\n", cmd.Filename.c_str());
        printf("Directory: %s\n", cmd.Directory.c_str());
        printf("Output: %s\n", cmd.Output.c_str());
    }
#endif

  auto generators = metapp::init_generators();

  /* The classFinder class is invoked as callback. */
  ClassFinder classFinder{outputOption.getValue(), std::move(generators)};
  MatchFinder finder;

  /* Search for all records (class/struct) with an 'annotate' attribute. */
  static DeclarationMatcher const classMatcher =
      cxxRecordDecl(decl().bind("id"), hasAttr(attr::Annotate));
  finder.addMatcher(classMatcher, &classFinder);

  /* Search for all fields with an 'annotate' attribute. */
  static DeclarationMatcher const propertyMatcher =
      fieldDecl(decl().bind("id"), hasAttr(attr::Annotate));
  finder.addMatcher(propertyMatcher, &classFinder);

  /* Search for all functions with an 'annotate' attribute. */
  static DeclarationMatcher const functionMatcher =
      functionDecl(decl().bind("id"), hasAttr(attr::Annotate));
  finder.addMatcher(functionMatcher, &classFinder);

  return tool.run(newFrontendActionFactory(&finder).get());
}
