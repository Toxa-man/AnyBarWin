#pragma once
#include <string>
#include <vector>

class NamedPipe
{
public:
    explicit NamedPipe(const std::string& pipeName);
    virtual void write(const std::vector<char>& message) = 0;
    virtual std::vector<char> read() const = 0;
    virtual ~NamedPipe() = default;
protected:
    const std::string name;
};
