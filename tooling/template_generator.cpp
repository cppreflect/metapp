#include <inja/inja.hpp>
#include <nlohmann/json.hpp>

#include "command_line.hpp"
#include "generator.hpp"
#include "template_generator.hpp"
#include "utils.hpp"

#include <exception>
#include <fstream>
#include <iterator>

static llvm::cl::opt<std::string>
    templateFile("template", llvm::cl::cat{g_ToolCategory},
                 llvm::cl::desc{"Input template file"},
                 llvm::cl::value_desc{"path"});


namespace metapp {

void TemplateGenerator::setup() {
  name("TemplateGenerator");
  // std::string input_filename = "templates/def.inja";
  std::string input_filename = templateFile.getValue();

  std::ifstream input(input_filename);

  if (input.is_open() == false) {
    throw std::runtime_error{"Could not open file " + input_filename};
  }
  m_template = std::string{std::istreambuf_iterator<char>(input),
                           std::istreambuf_iterator<char>()};
}

void TemplateGenerator::generate(clang::ASTContext *ctx, raw_ostream &os,
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

  if (reflectedClass.m_namespace) {
    reflectedClass.m_namespace->printQualifiedName(stos);
    data["qualifiedNamespace"] = std::string{type.begin(), type.end()};
    type.clear();
    reflectedClass.m_namespace->printName(stos);
    data["namespace"] = std::string{type.begin(), type.end()};
    type.clear();
  } 

  std::vector<std::string> fields;
  for (const auto &field : reflectedClass.m_fields) {
    field->printName(stos);
    fields.push_back(std::string{type.begin(), type.end()});
    type.clear();
  }
  data["fields"] = fields;

  os << inja::render(m_template, data);
}

} // namespace metapp

