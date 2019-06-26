#include "Utils.h"
#include <fstream>

namespace  Utils::Details
{
    std::string getCurrentTime()
    {
        std::string res(100, 0);
        SYSTEMTIME st;
        GetLocalTime(&st);
        sprintf_s(res.data(), 100, "[%.2u:%.2u:%.2u] ", st.wHour, st.wMinute, st.wSecond);
        return res;
    }

    void debugFunc(const char* str)
    {
        if constexpr (loggingEnabled) {
            std::ofstream out("anyBarServer.log", std::ios::app | std::ios::out);
            out << str;
        }
        OSPrintFunc(str);
    }
}
