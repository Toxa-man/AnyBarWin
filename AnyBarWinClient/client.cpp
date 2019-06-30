#include "NamedPipeWin.h"
#include "Protocol.h"
#include <iostream>
#include <algorithm>
#include <locale>

void printUsage()
{
    std::cout << "Usage: " << std::endl << std::endl <<
        "  " << "anybar" << " <image_name>" << std::endl <<
        "  " << "anybar" << " path" << " <path_to_file>" << std::endl <<
        "  " << "anybar" << " quit" << std::endl << std::endl;
    std::cout << "available images: transparent, white, red, green, blue, question" << std::endl;
}

void toLower(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return tolower(c); });
}

void checkFileFormat(const std::string_view& path)
{
    auto lastDotPos = path.find_last_of('.');
    if (lastDotPos == std::string::npos) {
        throw std::invalid_argument("Error: Invalid file format");
    }

    auto extension = static_cast<std::string>(path.substr(lastDotPos));
    toLower(extension);
    if (extension != ".ico") {
        throw std::invalid_argument("Error: only .ico images are allowed");
    }
}

bool startServer()
{
    STARTUPINFO info = { sizeof(info) };
    PROCESS_INFORMATION processInfo;
    if (CreateProcess("AnyBarWin.exe", nullptr, nullptr, nullptr, true, 0, nullptr, nullptr, &info, &processInfo)) {
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread); 
        return true;
    } 
    return false;
}

std::pair<Protocol::CommandType, std::string> parseUserInput(int argc, char* argv[])
{
    if (argc < 2 || argc > 3) {
        throw std::invalid_argument("Error: Wrong number of arguments");
    }

    if (argc == 2) {
        if (auto iter = Protocol::iconNamesMapper.find(argv[1]); iter != Protocol::iconNamesMapper.end()) {
            return { Protocol::Icon, std::to_string(iter->second) };
        }

        if (std::string_view(argv[1]) == "quit") {
            return { Protocol::Quit, "" };
        }

        if (std::string_view(argv[1]) == "start") {
            if (!startServer()) {
                throw std::runtime_error("Can't start server; Last error: " + std::to_string(GetLastError()));
            }
            return {Protocol::Invalid, ""};
        }
        checkFileFormat(argv[1]);
        return { Protocol::Path, argv[1]};
    }

    if (argc == 3) {
        if (std::string_view(argv[1]) != "path") {
            throw std::invalid_argument("");
        }

        checkFileFormat(argv[2]);
        return { Protocol::Path, argv[2] };
    }

    return  { Protocol::Invalid, "" };
}

int main(int argc, char* argv[])
{
    try {
        auto[cmd, message] = parseUserInput(argc, argv);
        if (cmd == Protocol::Invalid) {
            return 0;
        }
        NamedPipeWin pipe("anyBar", NamedPipe::Write);
        pipe.write(Protocol::packMessage(cmd, message));
    }
    catch (const std::runtime_error& e) {
        std::cout << "System error occured: " << e.what() << std::endl;
        std::cout << "May be you forgot to start the server?";
        return -2;
    }
    catch (const std::invalid_argument& e) {
        std::cout << std::endl << e.what() << std::endl << std::endl;
        printUsage();
        return -1;
    }

}
