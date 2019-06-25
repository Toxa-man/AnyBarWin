#pragma once
#include "Windows.h"
#include "TrayIconHandler.h"
#include <set>
#include <random>

class TrayIconHandlerWin :
    public TrayIconHandler
{
public:
    explicit TrayIconHandlerWin(HWND hWnd);
    ~TrayIconHandlerWin();
    TrayIconHandlerWin(TrayIconHandlerWin&& other) noexcept;
    TrayIconHandlerWin& operator = (TrayIconHandlerWin&& other) noexcept;
    void changeIcon(const std::string& iconName) override;
    void setPicture(const std::string& path) override;
private:
    HICON loadIcon(const std::string& iconName);
    static UINT getNewId();
    static std::mt19937 generator;
    UINT id = 0;
    static std::set<UINT> ids;
    NOTIFYICONDATA notifyData {};
};

