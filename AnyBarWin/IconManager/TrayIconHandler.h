#pragma once
#include <string>
#include <unordered_map>
#include "Protocol.h"

/**
 * \brief Represents the manager of unique icon in OS
 * 
 * The class satisfies the requirements of MoveConstructible and MoveAssignable, but not the requirements of either CopyConstructible or CopyAssignable.
 */
class TrayIconHandler
{
public:

    using Mapper = std::unordered_map<Protocol::IconName, int32_t>;
    /**
     * \brief Creates TrayIconHandler using name mapper
     * \param mapper Matches icon name from enum with it's OS-specific id
     */
    explicit TrayIconHandler(const Mapper& mapper);
    /**
     * \brief Changes icon using name iconName
     * \param iconName 
     */
    virtual void setIconByName(Protocol::IconName iconName) = 0;
    virtual void setIconByPath(const std::string& path) = 0;
    virtual ~TrayIconHandler() = default;
    TrayIconHandler(TrayIconHandler&&) = default;
    TrayIconHandler(const TrayIconHandler&) = delete;
    TrayIconHandler& operator = (const TrayIconHandler&) = delete;
    TrayIconHandler& operator = (TrayIconHandler&&) = default;
protected:
    /**
     * \brief maps enum name of icon to it's OS-specific id
     * \param data 
     * \return return OS-specific icon id and -1 if no such icon was found
     */
    int32_t iconNameToId(Protocol::IconName name);
    std::unordered_map<Protocol::IconName, int32_t> iconMapper;

};


