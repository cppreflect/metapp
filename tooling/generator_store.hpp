#pragma once

#include "generator.hpp"

namespace metapp {

struct GeneratorStore {

  static std::map<StringRef, std::unique_ptr<metapp::Generator>> m_generators;

  bool loadGenerator(std::unique_ptr<Generator> g) {
    StringRef name = g->name();
    auto r = m_generators.emplace(name, std::move(g));
    return r.second;
  }

  Generator* tryGet(StringRef name) {
    auto it = m_generators.find(name);
    if (it == m_generators.end()) {
      return nullptr;
    } 
    return it->second.get();
  }

};

}

