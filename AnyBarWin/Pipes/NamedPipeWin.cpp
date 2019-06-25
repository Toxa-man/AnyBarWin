#include "NamedPipeWin.h"
#include "../Utils.h"


NamedPipeWin::NamedPipeWin(const std::string& name, PipeType type) 
{
    const std::string osSpecName = R"(\\.\pipe\)" + name;

    if (type == Read || type == ReadWrite) {
        hPipe = CreateNamedPipe(
            osSpecName.c_str(),        
            type == Read ? PIPE_ACCESS_INBOUND : PIPE_ACCESS_DUPLEX,      
            PIPE_TYPE_MESSAGE |      
            PIPE_READMODE_MESSAGE |  
            PIPE_WAIT,                
            PIPE_UNLIMITED_INSTANCES, 
            buffSize,                  
            buffSize,                   
            0,                       
            nullptr);                   
    }  else {
        hPipe = CreateFile(
            osSpecName.c_str(),  
            GENERIC_WRITE,  
            0,             
            nullptr,           
            OPEN_EXISTING, 
            0,             
            nullptr);          
        DWORD dwMode = PIPE_READMODE_MESSAGE;
        SetNamedPipeHandleState(
            hPipe,     
            &dwMode, 
            nullptr,   
            nullptr);    
    }
    if (hPipe == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Can't create pipe");
    }
}

NamedPipeWin::NamedPipeWin(NamedPipeWin&& other) noexcept
{
    hPipe = other.hPipe;
    other.hPipe = INVALID_HANDLE_VALUE;
}

NamedPipeWin& NamedPipeWin::operator=(NamedPipeWin&& other) noexcept
{
    if (this == &other) {
        return *this;
    }
    FlushFileBuffers(hPipe);
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
    hPipe = other.hPipe;
    other.hPipe = INVALID_HANDLE_VALUE;
    return *this;
}

NamedPipeWin::~NamedPipeWin()
{
    FlushFileBuffers(hPipe);
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
}

void NamedPipeWin::write(const std::vector<char>& message)
{
    DWORD cbWritten;
    if (!WriteFile(
        hPipe,                
        message.data(),     
        message.size(),  
        &cbWritten,
        nullptr))
    {
        Utils::debug("Failed to write data to pipe\n", "Last error: ", GetLastError());
    }
}

std::vector<char> NamedPipeWin::read() const
{
    if (!ConnectNamedPipe(hPipe, nullptr)) {
        Utils::debug("Connect named pipe failed\n", "Last error: ", GetLastError());
        return {};
    }
    char inputBuffer[buffSize]{};
    DWORD bytesRead = 0;
    if (!ReadFile(
        hPipe,      
        inputBuffer,   
        buffSize,
        &bytesRead,
        nullptr)     
        ) {
        if (GetLastError() == ERROR_BROKEN_PIPE) {
            Utils::debug("Client disconnected");
        }
    }
    std::vector<char> result;
    result.reserve(bytesRead);
    std::copy(std::begin(inputBuffer), std::end(inputBuffer), std::back_inserter(result));
    return result;

}
