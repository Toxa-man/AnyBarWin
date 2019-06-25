#include "TrayIconHandler.h"


TrayIconHandler::TrayIconHandler(const std::unordered_map<std::string, int32_t>& mapper):
iconMapper {mapper}
{
}

int32_t TrayIconHandler::strToIconId(const std::string& data)
{
    auto iter = iconMapper.find(data);
    if (iter == iconMapper.end()) {
        return -1;
    }
    return iter->second;
}
