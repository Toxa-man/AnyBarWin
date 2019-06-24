#include "TrayIconHandlerWin.h"
#include "resource.h"
#include "HeadlessAppWin.h"

std::set<UINT> TrayIconHandlerWin::ids {};
std::mt19937 TrayIconHandlerWin::generator{ std::random_device{}() };

TrayIconHandlerWin::TrayIconHandlerWin(HWND hWnd):
    id{ getNewId() }
{
    auto defaultIcon = loadIcon(0);

    if (!defaultIcon) {
        OutputDebugStringA((std::string("Failed to load icon with id: ") + std::to_string(IDI_TRANSPARENT_ICON)).c_str());
        OutputDebugStringA((std::string("last error: ") + std::to_string(GetLastError())).c_str());
        return;
    }

    nidApp.cbSize = sizeof(NOTIFYICONDATA); // sizeof the struct in bytes
    nidApp.hWnd = (HWND)hWnd;              //handle of the window which will process this app. messages
    nidApp.uID = id;           //ID of the icon that willl appear in the system tray
    nidApp.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP; //ORing of all the flags
    nidApp.hIcon = defaultIcon; // handle of the Icon to be displayed, obtained from LoadIcon
    strcpy_s(nidApp.szTip, "test_tooltip");
    Shell_NotifyIcon(NIM_ADD, &nidApp);
}

TrayIconHandlerWin::~TrayIconHandlerWin()
{
    Shell_NotifyIcon(NIM_DELETE, &nidApp);
}

void TrayIconHandlerWin::changeIcon(const std::string& iconName)
{
    auto iconHandle = loadIcon(iconName);
    if (!iconHandle) {
        return;
    }
    nidApp.hIcon = iconHandle;
    Shell_NotifyIcon(NIM_MODIFY, &nidApp);
}

void TrayIconHandlerWin::setPicture(const std::string& path)
{
    //TODO: implement me
}

HICON TrayIconHandlerWin::loadIcon(const std::string& iconName)
{
    auto iconId = strToIconId(iconName);
    if (iconId == -1) {
        return nullptr;
    }
    return static_cast<HICON>(LoadImage(HeadlessAppWin::getHInstance(),
        MAKEINTRESOURCE(iconId), IMAGE_ICON,
        0,
        0, 0));
}

UINT TrayIconHandlerWin::getNewId()
{
    std::uniform_int_distribution<UINT> distrib(0, (std::numeric_limits<UINT>::max)());
    UINT result;
    do
    {
        result = distrib(generator);
    } while (ids.find(result) != ids.end());
    ids.insert(result);
    return result;
}
