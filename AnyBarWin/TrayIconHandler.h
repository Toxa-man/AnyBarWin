#pragma once
#include <string>
#include <unordered_map>

class TrayIconHandler
{
public:
    virtual void changeIcon(const std::string& iconName) = 0;
    virtual void setPicture(const std::string& path) = 0;
    virtual ~TrayIconHandler() = default;
protected:
    static int32_t strToIconId(const std::string& data);
    static std::unordered_map<std::string, int32_t> iconMapper;

};


