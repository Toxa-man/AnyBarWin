#include "TrayIconHandler.h"


TrayIconHandler::TrayIconHandler(const Mapper& mapper):
iconMapper {mapper}
{
}

int32_t TrayIconHandler::iconNameToId(Protocol::IconName name)
{
    auto iter = iconMapper.find(name);
    if (iter == iconMapper.end()) {
        return -1;
    }
    return iter->second;
}
