#pragma once
#include <string>
#include "Protocol.h"
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