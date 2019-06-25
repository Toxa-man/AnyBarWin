#pragma once
#include <vector>

class NamedPipe
{
public:
    NamedPipe() = default;
    NamedPipe(const NamedPipe&) = delete;
    NamedPipe& operator = (const NamedPipe&) = delete;
    NamedPipe(NamedPipe&&) = default;
    NamedPipe& operator = (NamedPipe&&) = default;

    enum PipeType { Read, Write, ReadWrite };
    virtual void write(const std::vector<char>& message) = 0;
    virtual std::vector<char> read() const = 0;
    virtual ~NamedPipe() = default;
};
