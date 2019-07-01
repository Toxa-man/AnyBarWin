#pragma once
#include "NamedPipeWin.h"
#include "Protocol.h"
#include <iostream>
#include "ClientLogic.h"


int main(int argc, char* argv[])
{
    try {
        auto[cmd, message] = parseUserInput(argc, argv);
        if (cmd == Protocol::Invalid) {
            return 0;
        }
        NamedPipeWin pipe(Protocol::pipeName, NamedPipe::Write);
        pipe.write(Protocol::packMessage(cmd, message));
    }
    catch (const std::runtime_error& e) {
        std::cout << "System error occured: " << e.what() << std::endl;
        std::cout << "May be you forgot to start the server?";
        return -1;
    }
    catch (const std::invalid_argument& e) {
        std::cout << std::endl << e.what() << std::endl << std::endl;
        printUsage();
        return -2;
    }
    catch (const std::logic_error& e) {
        std::cout << std::endl << e.what() << std::endl;
        return -3;
    }

}


