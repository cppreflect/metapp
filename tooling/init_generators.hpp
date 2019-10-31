#ifndef LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_INIT_GENERATORS_HPP
#define LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_INIT_GENERATORS_HPP
#pragma once

#include "generator_store.hpp"

namespace metapp {

std::shared_ptr<GeneratorStore> init_generators();

} // namespace metapp

#endif // LLVM_CLANG_TOOLS_EXTRA_METAPP_TOOLING_INIT_GENERATORS_HPP
