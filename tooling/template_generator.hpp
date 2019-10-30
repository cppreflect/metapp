#pragma once

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>

#include "generator.hpp"
#include "utils.hpp"

#include <fstream>
#include <iterator>
#include <exception>

// struct TemplateError : std::runtime_error {
//
//   TemplateError(std::string err) : m_what{std::move(err)} {}
//   TemplateError(const char* err) : m_what{err} {}
//
//   const char* what() const override {
//     return what.c_str();
//   }
//
//   std::string m_what;
// }


// static llvm::cl::OptionCategory g_TemplateCategory("Template parameters");
static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static llvm::cl::opt<std::string>
    templateFile("template", //llvm::cl::cat{g_TemplateCategory},
                 llvm::cl::desc{"Input template file"},
                 llvm::cl::value_desc{"path"});
// static llvm::cl::alias outputAlias("o", llvm::cl::cat{g_ToolCategory},
//                                    llvm::cl::desc{"Alias for output"},
//                                    llvm::cl::value_desc{"filename"},
//                                    llvm::cl::aliasopt{outputOption});



namespace metapp {

struct TemplateGenerator : public Generator {
  void setup() {
    name("TemplateGenerator");
    // std::string input_filename = "templates/def.inja";
    std::string input_filename = templateFile.getValue();

    std::ifstream input(input_filename);

    if (input.is_open() == false) {
      throw std::runtime_error{"Could not open file" + input_filename};
    }
    m_template = std::string{std::istreambuf_iterator<char>(input),
                             std::istreambuf_iterator<char>()};
  }

  void generate(ASTContext *ctx, raw_ostream &os,
                ReflectedClass const &reflectedClass) const {


    // Just for convenience
    using namespace inja;
    using json = nlohmann::json;

    json data;

    SmallString<64> type;
    raw_svector_ostream stos(type);
    reflectedClass.m_record->printQualifiedName(stos);

    data["type"] = std::string{type.begin(), type.end()};
    type.clear();
    //
    std::vector<std::string> fields;
    for (const auto& field : reflectedClass.m_fields) {
      field->printName(stos);
      fields.push_back(std::string{type.begin(), type.end()});
      type.clear();
    }
    data["fields"] = fields;

    os << inja::render(m_template, data);
  }

private:
  std::string m_template;
};

} // namespace metapp

