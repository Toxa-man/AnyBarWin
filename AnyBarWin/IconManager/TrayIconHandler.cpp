#include "TrayIconHandler.h"


int32_t TrayIconHandler::strToIconId(const std::string& data)
{
    auto iter = iconMapper.find(data);
    if (iter == iconMapper.end()) {
        return -1;
    }
    return iter->second;
}
