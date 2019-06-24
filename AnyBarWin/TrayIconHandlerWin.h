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
    void changeIcon(const std::string& iconName) override;
    void setPicture(const std::string& path) override;
private:
    static HICON loadIcon(const std::string& iconName);
    static UINT getNewId();
    static std::mt19937 generator;
    const UINT id = 0;
    HWND hWnd;
    UINT current_icon_id = 0;
    static std::set<UINT> ids;
    NOTIFYICONDATA nidApp;
};
