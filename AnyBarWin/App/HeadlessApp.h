#pragma once
#include <memory>

class HeadlessApp
{
public:
    virtual void startEventLoop() = 0;
    virtual ~HeadlessApp() = default;
protected:
    std::unique_ptr<class TrayIconHandler> iconHandler;
};
