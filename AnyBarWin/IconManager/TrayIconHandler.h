#pragma once
#include <string>
#include <unordered_map>

/**
 * \brief Represents the manager of unique icon in OS
 * 
 * The class satisfies the requirements of MoveConstructible and MoveAssignable, but not the requirements of either CopyConstructible or CopyAssignable.
 */
class TrayIconHandler
{
public:
    /**
     * \brief Creates TrayIconHandler using mapper
     * \param mapper - Matches string name of icon and it's OS-specific id
     */
    explicit TrayIconHandler(const std::unordered_map<std::string, int32_t>& mapper);
    /**
     * \brief Changes icon using name iconName
     * \param iconName 
     */
    virtual void setIconByName(const std::string& iconName) = 0;
    virtual void setIconByPath(const std::string& path) = 0;
    virtual ~TrayIconHandler() = default;
    TrayIconHandler(TrayIconHandler&&) = default;
    TrayIconHandler(const TrayIconHandler&) = delete;
    TrayIconHandler& operator = (const TrayIconHandler&) = delete;
    TrayIconHandler& operator = (TrayIconHandler&&) = default;
protected:
    /**
     * \brief maps string name of icon to it's OS-specific id
     * \param data 
     * \return return OS-specific icon id and -1 if no such icon was found
     */
    int32_t strToIconId(const std::string& data);
    std::unordered_map<std::string, int32_t> iconMapper;

};


