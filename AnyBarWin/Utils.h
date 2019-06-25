#pragma once
#include <functional>
#include <debugapi.h>
#include <string>

namespace Utils
{
    namespace Details
    {
        static std::function<void(const char*)> debugFunc

#ifdef _WIN32
            = OutputDebugString
#endif
#ifdef __linux__
            = puts
#endif
            ;
        template <typename T>
        std::enable_if_t<std::is_convertible_v<std::decay_t<T>, const char*>>
            print(T&& t)
        {
            debugFunc(t);
        }

        template <typename T>
        std::enable_if_t<std::is_same_v<std::decay_t<T>, char>>
            print(T&& t)
        {
            std::string str{ t };
            debugFunc(str.c_str());
        }

        template <typename T>
        std::enable_if_t<
            std::is_arithmetic_v<std::decay_t<T>> &&
            !std::is_same_v<std::decay_t<T>, char>>
            print(T&& t)
        {
            debugFunc(std::to_string(t).c_str());
        }

        template <typename T>
        std::enable_if_t<std::is_same_v<std::decay_t<T>, std::string>>
            print(T&& t)
        {
            debugFunc(t.c_str());
        }
    }


    template <typename... Args>
    void debug(Args&&... args)
    {
        using Details::print;
        (..., print(std::forward<Args>(args)));

    }
}
