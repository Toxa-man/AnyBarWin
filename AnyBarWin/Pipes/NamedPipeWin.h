#pragma once
#include "Windows.h"
#include "NamedPipe.h"

class NamedPipeWin :
    public NamedPipe
{
public:
    NamedPipeWin(const std::string& name, PipeType type);
    NamedPipeWin(NamedPipeWin&&) noexcept;
    NamedPipeWin& operator = (NamedPipeWin&&) noexcept;
    ~NamedPipeWin();
    void write(const std::vector<char>& message) override;
    std::vector<char> read() const override;
private:
    HANDLE hPipe;
    constexpr static std::size_t buffSize = 1024;
};

