#pragma once
#include <vector>
#include <string>

namespace Protocol {
    enum CommandType { Icon, Path, Quit };

    std::vector<char> packMessage(CommandType command, const std::string& parameter);

    std::pair<CommandType, std::string> unpackMessage(const char* data, std::size_t bytesRead);
}
