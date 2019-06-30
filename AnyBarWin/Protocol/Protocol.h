#pragma once
#include <vector>
#include <string>
#include <unordered_map>

namespace Protocol {
    enum CommandType {Invalid, Icon, Path, Quit };

    enum IconName {Transparent, Red, White, Green, Blue, Question};

    const std::string pipeName = "anyBar";

    const std::unordered_map<std::string, IconName> iconNamesMapper = {
        {"transparent", Transparent},
        {"red", Red},
        {"white", White},
        {"green", Green},
        {"blue", Blue},
        {"question", Question},
    };

    /**
     * \brief Packs message to vector<char>
     * \param command 
     * \param parameter 
     * \return 
     * 
     * Output data has the following format:
     * 0-3 bytes - command
     * 4-7 bytes - parameter length
     * 8-parameter_length - parameter as the NON-nullterminated sequence of chars
     */
    std::vector<char> packMessage(CommandType command, const std::string& parameter);

    /**
     * \brief Unpack the result of Protocol::packMessage
     * \param data 
     * \param bytesRead number of bytes received
     * \return 
     * 
     * throws std::runtimer_error in case of invalid data format
     */
    std::pair<CommandType, std::string> unpackMessage(const char* data, std::size_t bytesRead);
}
