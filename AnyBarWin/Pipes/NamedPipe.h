#pragma once
#include <vector>

/**
 * \brief Represents named pipe with different communication modes
 * 
 * The class satisfies the requirements of MoveConstructible and MoveAssignable, but not the requirements of either CopyConstructible or CopyAssignable.
 */
class NamedPipe
{
public:
    NamedPipe() = default;
    NamedPipe(const NamedPipe&) = delete;
    NamedPipe& operator = (const NamedPipe&) = delete;
    NamedPipe(NamedPipe&&) = default;
    NamedPipe& operator = (NamedPipe&&) = default;

    /**
     * \brief Pipe creation type
     */
    enum PipeType
    {
        Read, 
        Write, 
        ReadWrite
    };
    /**
     * \brief Writes packed message to pipe
     * \param message packed message
     */
    virtual void write(const std::vector<char>& message) = 0;
    /**
     * \brief Blocks execution until new data arrived and returns it as packed data
     * \return returns packed data. Use Protocol::unpackMessage to get command and message
     */
    virtual std::vector<char> read() const = 0;
    virtual ~NamedPipe() = default;
};
