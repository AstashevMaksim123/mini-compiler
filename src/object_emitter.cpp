#include "object_emitter.hpp"

#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

namespace mini {

bool emitObjectFile(llvm::Module& module, const std::string& outputPath, std::string& errorMessage) {
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    std::string targetTriple = module.getTargetTriple();
    std::string lookupError;
    const llvm::Target* target = llvm::TargetRegistry::lookupTarget(targetTriple, lookupError);
    if (target == nullptr) {
        errorMessage = lookupError;
        return false;
    }

    llvm::TargetOptions options;
    std::unique_ptr<llvm::TargetMachine> targetMachine(
        target->createTargetMachine(targetTriple, "generic", "", options, llvm::Reloc::PIC_));
    if (!targetMachine) {
        errorMessage = "failed to create LLVM target machine";
        return false;
    }

    module.setDataLayout(targetMachine->createDataLayout());
    module.setTargetTriple(targetTriple);

    std::error_code ec;
    llvm::raw_fd_ostream dest(outputPath, ec, llvm::sys::fs::OF_None);
    if (ec) {
        errorMessage = ec.message();
        return false;
    }

    llvm::legacy::PassManager passManager;
    if (targetMachine->addPassesToEmitFile(passManager, dest, nullptr, llvm::CodeGenFileType::ObjectFile)) {
        errorMessage = "target machine cannot emit object files";
        return false;
    }

    passManager.run(module);
    dest.flush();
    errorMessage.clear();
    return true;
}

}  // namespace mini
