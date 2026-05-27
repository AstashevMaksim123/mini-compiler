#pragma once

#include <string>

namespace mini {

struct SourceLocation {
    int line = 1;
    int column = 1;
};

struct SourceRange {
    SourceLocation begin;
    SourceLocation end;
};

inline std::string formatLocation(const SourceRange& range) {
    return std::to_string(range.begin.line) + ":" + std::to_string(range.begin.column);
}

}  // namespace mini

