#pragma once
#include <string>
#include <optional>

class InputParser {
public:
    // 문자열이 정수이면 해당 값 반환, 아니면 nullopt
    std::optional<int> parseNumber(const std::string& input) const;

    bool isExitCommand(const std::string& input) const;
};
