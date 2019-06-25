#pragma once
#include "Windows.h"
#include "NamedPipe.h"

/**
 * \brief Represents Windows-specific named pipe
 */
class NamedPipeWin :
    public NamedPipe
{
public:
    /**
     * \brief Creates pipe with WinApi pipes pattern name (\\.\pipe\pipeName)
     * \param name pipe name WITHOUT os-specific details
     * \param type connection mode
     * 
     * if type is PipeType::Read - pipe is created using CreateNamedPipe with PIPE_ACCESS_INBOUND parameter (server mode)
     * if type is PipeType::ReadWrite - pipe is created using CreateNamedPipe with PIPE_ACCESS_DUPLEX parameter (server mode)
     * if type is PipeType::Write - pipe is opening using CreateFile with write mode (client mode)
     */
    NamedPipeWin(const std::string& name, PipeType type);
    NamedPipeWin(NamedPipeWin&&) noexcept;
    NamedPipeWin& operator = (NamedPipeWin&&) noexcept;
    ~NamedPipeWin();
    void write(const std::vector<char>& message) override;
    std::vector<char> read() const override;
private:
    /**
     * \brief Pipe handle
     */
    HANDLE hPipe;
    constexpr static std::size_t buffSize = 1024;
};

