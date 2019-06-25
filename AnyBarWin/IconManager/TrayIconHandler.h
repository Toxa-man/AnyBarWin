#pragma once
#include <string>
#include <unordered_map>

class TrayIconHandler
{
public:
    explicit TrayIconHandler(const std::unordered_map<std::string, int32_t>& mapper);
    virtual void changeIcon(const std::string& iconName) = 0;
    virtual void setPicture(const std::string& path) = 0;
    virtual ~TrayIconHandler() = default;
    TrayIconHandler(TrayIconHandler&&) = default;
    TrayIconHandler(const TrayIconHandler&) = delete;
    TrayIconHandler& operator = (const TrayIconHandler&) = delete;
    TrayIconHandler& operator = (TrayIconHandler&&) = default;
protected:
    int32_t strToIconId(const std::string& data);
    std::unordered_map<std::string, int32_t> iconMapper;

};


