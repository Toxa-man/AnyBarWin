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
        static std::function<void(const char*)> OSPrintFunc

#ifdef _WIN32
            = OutputDebugString
#endif
#ifdef __linux__
            = puts
#endif
            ;

        std::string getCurrentTime();

        static constexpr bool loggingEnabled = true;

        void debugFunc(const char* str);

        /**
         * \brief Determines the type category of T and performs relevant conversions to const char* 
         * \tparam T argument type
         * \param t argument value
         * 
         * This function uses if constexpr feature from c++17
         */
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


    /**
     * \brief 
     * \tparam Args Parameter pack of arguments to be printed
     * \param args 
     * 
     * This function uses fold expressions feature from c++17
     */
    template <typename... Args>
    void debug(Args&&... args)
    {
        using Details::print;
        if constexpr (Details::loggingEnabled){
            print(Details::getCurrentTime());
        }
        (..., print(std::forward<Args>(args)));
        print('\n');

    }
}
