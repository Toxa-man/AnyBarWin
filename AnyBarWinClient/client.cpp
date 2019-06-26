#include "NamedPipeWin.h"
#include "Protocol.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3) {
        std::cout << "Usage: " << std::endl << std::endl <<
            "  " << "anybar" << " <image_name>" << std::endl <<
            "  " << "anybar" << " path" << " <path_to_file>" << std::endl <<
            "  " << "anybar" << " quit" << std::endl << std::endl;
        std::cout << "available images: transparent, white, red, green, blue, question" << std::endl;
        return -1;
    }
    try {
        NamedPipeWin pipe("anyBar", NamedPipe::Write);
        if (argc == 2) {
            if (strcmp(argv[1], "quit") == 0) {
                pipe.write(Protocol::packMessage(Protocol::Quit, ""));
            }
            else {
                pipe.write(Protocol::packMessage(Protocol::Icon, argv[1]));
            }

        }
        else {
            pipe.write(Protocol::packMessage(Protocol::Path, argv[2]));
        }
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error occured: " << e.what();
    }

}
