#pragma once
#include <functional>
#ifdef _WIN32
#include "Windows.h"
#endif
#ifdef __linux__
#include <stdio.h>
#endif
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

        template<typename T>
        void print(T&& t)
        {
            if constexpr (std::is_convertible_v<std::decay_t<T>, const char*>){
                debugFunc(t);
            } else if constexpr (std::is_same_v<std::decay_t<T>, char>){
                std::string str{ t };
                debugFunc(str.c_str());
            } else if constexpr (std::is_arithmetic_v<std::decay_t<T>> &&
                !std::is_same_v<std::decay_t<T>, char > ) {
                debugFunc(std::to_string(t).c_str());
            } else if constexpr (std::is_same_v<std::decay_t<T>, std::string>){
                debugFunc(t.c_str());
            }
        }
    }


    template <typename... Args>
    void debug(Args&&... args)
    {
        using Details::print;
        (..., print(std::forward<Args>(args)));
        print('\n');

    }
}
