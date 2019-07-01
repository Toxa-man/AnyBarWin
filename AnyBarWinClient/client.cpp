#include "NamedPipeWin.h"
#include "Protocol.h"
#include <iostream>
#include <algorithm>
#include <thread>

void printUsage();

/**
 * \brief Do in-place string transforming to lower case using C tolower func
 * \param str string to transform
 */
void toLower(std::string& str);

/**
 * \brief check file format using it's extension for the ablility to be used as icon
 * \param path 
 * 
 * The only supported format for now is .ico. Throws an std::invalid_argument if format is invalid
 */
void checkFileFormat(const std::string_view& path);

/**
 * \brief start process from server binary using OS-specific calls
 * \return true on success, false otherwise
 */
bool startServer();

/**
 * \brief checks if server is running
 * \return true if server is running and false otherwise
 */
bool checkIfServerIsRunning();

/**
 * \brief tries to start server by calling startServer
 * \return true on success and false otherwise
 */
bool tryStartServer();

/**
 * \brief parse command line arguments when one parameter was passed
 * \param arg command line argument to parse
 * \return pair of command and parameter
 */
std::pair<Protocol::CommandType, std::string> parseOneArgument(std::string_view arg);

/**
 * \brief parse command line arguments when two parameters were passed
 * \param arg1 command line argument to parse
 * \param arg2 command line argument to parse
 * \return pair of command and parameter
 */
std::pair<Protocol::CommandType, std::string> parseTwoArguments(std::string_view arg1, std::string_view arg2);

/**
 * \brief parses command line arguments
 * \param argc 
 * \param argv 
 * \return pair of command and parameter
 */
std::pair<Protocol::CommandType, std::string> parseUserInput(int argc, char* argv[]);



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
#ifdef WIN32
    STARTUPINFO info = { sizeof(info) };
    PROCESS_INFORMATION processInfo;
    if (CreateProcess("AnyBarWin.exe", nullptr, nullptr, nullptr, true, 0, nullptr, nullptr, &info, &processInfo)) {
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
        return true;
    }
#endif
    return false;
}

bool checkIfServerIsRunning()
{
    bool res = false;
#ifdef WIN32
    auto hMutex = CreateMutex(nullptr,
        FALSE,
        TEXT("InstanceGuardMutex"));
    res = GetLastError() == ERROR_ALREADY_EXISTS;
    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
#endif
    return res;
}

bool tryStartServer()
{
    if (!checkIfServerIsRunning()) {
        if (!startServer()) {
            std::cout << "can't start server, last error: " << GetLastError();
        }
        return true;
    }
    return false;
}

std::pair<Protocol::CommandType, std::string> parseOneArgument(std::string_view arg)
{
    if (auto iter = Protocol::iconNamesMapper.find(arg); iter != Protocol::iconNamesMapper.end()) {
        tryStartServer();
        return { Protocol::Icon, std::to_string(iter->second) };
    }

    if (arg == "quit") {
        return { Protocol::Quit, "" };
    }

    if (arg == "start") {
        if (checkIfServerIsRunning()) {
            throw std::logic_error("Server is already running");
        }
        if (!startServer()) {
            throw std::runtime_error("Can't start server; Last error: " + std::to_string(GetLastError()));
        }
        return { Protocol::Invalid, "" };
    }
    checkFileFormat(arg);
    tryStartServer();

    return { Protocol::Path, static_cast<std::string>(arg) };
}

std::pair<Protocol::CommandType, std::string> parseTwoArguments(std::string_view arg1, std::string_view arg2)
{
    if (std::string_view(arg1) != "path") {
        throw std::invalid_argument("");
    }

    checkFileFormat(arg2);
    if (!checkIfServerIsRunning()) {
        startServer();
    }
    return { Protocol::Path, static_cast<std::string>(arg2) };

}

std::pair<Protocol::CommandType, std::string> parseUserInput(int argc, char* argv[])
{
    if (argc < 2 || argc > 3) {
        throw std::invalid_argument("Error: Wrong number of arguments");
    }

    if (argc == 2) {
        return parseOneArgument(argv[1]);
    }

    if (argc == 3) {
        return parseTwoArguments(argv[1], argv[2]);
    }

    return  { Protocol::Invalid, "" };
}
