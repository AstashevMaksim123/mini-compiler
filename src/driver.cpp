#include "codegen.hpp"
#include "object_emitter.hpp"
#include "parser_context.hpp"
#include "sema.hpp"

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int yyparse(mini::ParserContext& ctx);
extern FILE* yyin;

namespace {

struct Options {
    std::string inputFile;
    std::string outputFile;
    std::string targetTriple = "x86_64-pc-linux-gnu";
    bool emitIr = false;
};

void printUsage() {
    std::cerr << "usage: mini_cc input.mc [-o output.o] [--emit-ir] [--target triple]\n";
}

bool parseArgs(int argc, char** argv, Options& options) {
    if (argc < 2) {
        printUsage();
        return false;
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-o") {
            if (i + 1 >= argc) {
                std::cerr << "missing output path after -o\n";
                return false;
            }
            options.outputFile = argv[++i];
        } else if (arg == "--emit-ir") {
            options.emitIr = true;
        } else if (arg == "--target") {
            if (i + 1 >= argc) {
                std::cerr << "missing target triple after --target\n";
                return false;
            }
            options.targetTriple = argv[++i];
        } else if (!arg.empty() && arg[0] == '-') {
            std::cerr << "unknown option: " << arg << '\n';
            return false;
        } else if (options.inputFile.empty()) {
            options.inputFile = arg;
        } else {
            std::cerr << "unexpected argument: " << arg << '\n';
            return false;
        }
    }

    if (options.inputFile.empty()) {
        std::cerr << "input file is required\n";
        return false;
    }
    if (options.outputFile.empty()) {
        options.outputFile = "generated.o";
    }
    return true;
}

std::string irPathForObject(const std::string& objectPath) {
    std::filesystem::path path(objectPath);
    path.replace_extension(".ll");
    return path.string();
}

}  // namespace

int main(int argc, char** argv) {
    Options options;
    if (!parseArgs(argc, argv, options)) {
        return 1;
    }

    yyin = std::fopen(options.inputFile.c_str(), "r");
    if (yyin == nullptr) {
        std::perror(options.inputFile.c_str());
        return 1;
    }

    mini::ParserContext context(options.inputFile);
    if (yyparse(context) != 0 || context.hasErrors() || !context.program) {
        std::cerr << context.formatDiagnostics();
        std::fclose(yyin);
        return 1;
    }
    std::fclose(yyin);

    mini::SemanticAnalyzer sema(context);
    if (!sema.analyze(*context.program)) {
        std::cerr << context.formatDiagnostics();
        return 1;
    }

    mini::CodeGenerator codegen(options.inputFile, options.targetTriple);
    std::string errorMessage;
    if (!codegen.generate(*context.program, errorMessage)) {
        std::cerr << errorMessage << '\n';
        return 1;
    }

    if (options.emitIr) {
        std::error_code ec;
        llvm::raw_fd_ostream irOut(irPathForObject(options.outputFile), ec);
        if (ec) {
            std::cerr << ec.message() << '\n';
            return 1;
        }
        codegen.module().print(irOut, nullptr);
    }

    if (!mini::emitObjectFile(codegen.module(), options.outputFile, errorMessage)) {
        std::cerr << errorMessage << '\n';
        return 1;
    }

    return 0;
}

