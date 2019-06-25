#pragma once
#include <memory>
#include <string>
#include "NamedPipe.h"

/**
 * \brief 
 * Describes hidden application with pipe cycle 
 * 
 * The class satisfies the requirements of MoveConstructible and MoveAssignable, but not the requirements of either CopyConstructible or CopyAssignable.
 */
class HeadlessApp
{
public:
    /**
     * \brief Start accepting commands via named pipes. 
     * 
     * Calling this function blocks execution thread until quit command won't be received
     */
    virtual void startEventLoop();
    virtual ~HeadlessApp() = default;
    HeadlessApp(const HeadlessApp&) = delete;
    HeadlessApp& operator =(const HeadlessApp&) = delete;
    HeadlessApp(HeadlessApp&&) = default;
    HeadlessApp& operator = (HeadlessApp&&) = default;
protected:
    HeadlessApp() = default;

    /**
     * \brief Creates OS-Specific pipe type and returns std::shared_ptr to this type
     * \param name pipe name without any os-specific formats
     * \param type 
     * \return std::shared_ptr to base class that have OS-specific dynamic type
     */
    virtual std::shared_ptr<NamedPipe> makePipe(const std::string& name, NamedPipe::PipeType type) = 0;
    /**
     * \brief unique_ptr to base type of IconHandler
     */
    std::unique_ptr<class TrayIconHandler> iconHandler;
};

