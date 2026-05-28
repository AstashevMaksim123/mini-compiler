#pragma once

#include "ast.hpp"

#include <memory>
#include <string>
#include <vector>

namespace mini {

struct Diagnostic {
    SourceRange range;
    std::string message;

};

class ParserContext {
public:
    explicit ParserContext(std::string fileName);

    void report(const SourceRange& range, std::string message);
    bool hasErrors() const;
    std::string formatDiagnostics() const;

    std::string fileName;
    std::unique_ptr<Program> program;
    std::vector<Diagnostic> diagnostics;
};

}  // namespace mini

