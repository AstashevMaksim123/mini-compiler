#pragma once

#include <llvm/IR/Module.h>

#include <string>

namespace mini {

bool emitObjectFile(llvm::Module& module, const std::string& outputPath, std::string& errorMessage);

}  // namespace mini
