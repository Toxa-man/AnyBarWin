#pragma once
#include "Windows.h"
#include "NamedPipe.h"

class NamedPipeWin :
    public NamedPipe
{
public:
    NamedPipeWin(const std::string& name, DWORD dwPipeMode);
    ~NamedPipeWin();
    void write(const std::vector<char>& message) override;
    std::vector<char> read() const override;
private:
    HANDLE hPipe;
};

