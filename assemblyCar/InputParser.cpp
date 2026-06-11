#include "InputParser.h"
#include <stdexcept>

std::optional<int> InputParser::parseNumber(const std::string& input) const {
    if (input.empty()) return std::nullopt;
    try {
        std::size_t processed = 0;
        int value = std::stoi(input, &processed);
        if (processed != input.size()) return std::nullopt; // 뒤에 비숫자 문자 있음
        return value;
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

bool InputParser::isExitCommand(const std::string& input) const {
    return input == "exit";
}
