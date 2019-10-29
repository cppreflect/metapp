#include "init_generators.hpp"
#include "generator.hpp"
#include "runtime_reflection_generator.hpp"


namespace metapp {

std::shared_ptr<GeneratorStore> init_generators() {

  auto generatorStore = std::make_shared<GeneratorStore>();

  auto runtimeGenerator = std::make_unique<RuntimeReflectionGenerator>();
  auto rg = runtimeGenerator.get();
  runtimeGenerator->setup();
  generatorStore->loadGenerator(std::move(runtimeGenerator));

  auto i = generatorStore->tryGet(rg->name());

  assert(i != nullptr && "Generator not found");

  return generatorStore;
}

} // namespace metapp
