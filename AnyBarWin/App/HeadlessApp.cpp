#include "HeadlessApp.h"
#include "../Utils.h"
#include "../IconManager/TrayIconHandler.h"
#include "../Protocol/Protocol.h"

void HeadlessApp::startEventLoop()
{
    bool exit = false;
    while (!exit) {
        auto pipe = makePipe("anyBar", NamedPipe::Read);

        auto data = pipe->read();

        try {
            auto[command, message] = Protocol::unpackMessage(data.data(), data.size());
            switch (command) {
            case Protocol::Icon: iconHandler->setIconByName(message); break;
            case Protocol::Path: iconHandler->setIconByPath(message); break;
            case Protocol::Quit: exit = true; break;
            default:
                Utils::debug("Wrong type of command: ", command);
            }
        }
        catch (const std::runtime_error& e) {
            Utils::debug(e.what());
        }


    }
}
