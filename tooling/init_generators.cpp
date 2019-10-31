#include "init_generators.hpp"
#include "generator.hpp"
#include "runtime_reflection_generator.hpp"
#include "template_generator.hpp"


namespace metapp {

std::shared_ptr<GeneratorStore> init_generators() {

  auto generatorStore = std::make_shared<GeneratorStore>();

  auto runtimeGenerator = std::make_unique<RuntimeReflectionGenerator>();
  runtimeGenerator->setup();
  generatorStore->loadGenerator(std::move(runtimeGenerator));

  auto templateGenerator = std::make_unique<TemplateGenerator>();
  templateGenerator->setup();
  generatorStore->loadGenerator(std::move(templateGenerator));

  return generatorStore;
}

} // namespace metapp
