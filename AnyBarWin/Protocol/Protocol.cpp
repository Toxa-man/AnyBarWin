#include  "Protocol.h"

std::vector<char> Protocol::packMessage(CommandType command, const std::string& parameter)
{
    std::size_t dataSize = sizeof(int32_t) + sizeof(int32_t) + parameter.length();
    std::vector<char> result;
    result.resize(dataSize);
    auto ptr = result.data();
    int32_t cmd = command;
    int32_t length = parameter.length();
    memcpy(ptr, &cmd, sizeof(int32_t));
    ptr += sizeof(int32_t);
    memcpy(ptr, &length, sizeof(int32_t));
    ptr += sizeof(int32_t);
    memcpy(ptr, parameter.data(), parameter.length());
    return result;
}

std::pair<Protocol::CommandType, std::string> Protocol::unpackMessage(const char* data, std::size_t bytesRead)
{
    if (bytesRead < sizeof(int32_t) * 2) {
        throw std::runtime_error("Can't parse command type or message length");
    }
    int32_t cmd;
    int32_t length;
    memcpy(&cmd, data, sizeof(int32_t));
    data += sizeof(int32_t);
    memcpy(&length, data, sizeof(int32_t));
    data += sizeof(int32_t);
    if (bytesRead < sizeof(int32_t) * 2 + length) {
        throw std::runtime_error("Can't parse message");
    }
    std::string parameter(data, length);
    return {static_cast<CommandType>(cmd), parameter};
}
