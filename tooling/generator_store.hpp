#pragma once

#include "generator.hpp"
#include <iostream>

namespace metapp {

struct GeneratorStore {

  std::map<std::string, std::unique_ptr<metapp::Generator>> m_generators;

  bool loadGenerator(std::unique_ptr<Generator> g) {
    std::string name = g->name();
    auto r = m_generators.emplace(name, std::move(g));
    return r.second;
  }

  Generator *tryGet(std::string name) {
    auto it = m_generators.find(name);
    if (it == m_generators.end()) {
      return nullptr;
    }
    return it->second.get();
  }

  Generator *mockGet(std::string name) {
    auto i = tryGet("TemplateGenerator");

    if (i == nullptr) {
      std::cout << "VRISTI" << std::endl;
    }
    assert(i != nullptr && "Generator NotFound");
    return i;
  }
};

} // namespace metapp
