#pragma once
#include <memory>
#include <string>
#include "NamedPipe.h"

class HeadlessApp
{
public:
    virtual void startEventLoop();
    virtual ~HeadlessApp() = default;
    HeadlessApp(const HeadlessApp&) = delete;
    HeadlessApp& operator =(const HeadlessApp&) = delete;
    HeadlessApp(HeadlessApp&&) = default;
    HeadlessApp& operator = (HeadlessApp&&) = default;
protected:
    HeadlessApp() = default;
    virtual std::shared_ptr<NamedPipe> makePipe(const std::string& name, NamedPipe::PipeType type) = 0;
    std::unique_ptr<class TrayIconHandler> iconHandler;
};

