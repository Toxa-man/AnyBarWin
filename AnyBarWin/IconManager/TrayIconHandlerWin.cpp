#include "TrayIconHandlerWin.h"
#include "../resource.h"
#include "HeadlessAppWin.h"
#include "../Utils.h"

std::set<UINT> TrayIconHandlerWin::ids {};
std::mt19937 TrayIconHandlerWin::generator{ std::random_device{}() };

TrayIconHandlerWin::TrayIconHandlerWin(HWND hWnd):
    TrayIconHandler(
        {
            {Protocol::White, IDI_WHITE},
            {Protocol::Red, IDI_RED},
            {Protocol::Green, IDI_GREEN},
            {Protocol::Blue, IDI_BLUE},
            {Protocol::Question, IDI_QUEST},
            {Protocol::Transparent, IDI_TRANSPARENT},
            {Protocol::Exclamation, IDI_EXCLAM},
            {Protocol::Black, IDI_BLACK},
            {Protocol::Yellow, IDI_YELLOW},
            {Protocol::Orange, IDI_ORANGE},
            {Protocol::Purple, IDI_PURPLE},
            {Protocol::Cyan, IDI_CYAN},
        }
    ),
    id{getNewId()}

{
    auto defaultIcon = loadIconFromResource(Protocol::Transparent);

    if (!defaultIcon) {
        Utils::debug("Failed to load icon with id: ", iconNameToId(Protocol::Transparent));
        Utils::debug("last error: ", GetLastError());
        return;
    }

    notifyData.cbSize = sizeof(NOTIFYICONDATA);
    notifyData.hWnd = hWnd;
    notifyData.uID = id;
    notifyData.uFlags = NIF_ICON | NIF_TIP;
    notifyData.hIcon = defaultIcon;
    strcpy_s(notifyData.szTip, "It Works!");
    Shell_NotifyIcon(NIM_ADD, &notifyData);
}

TrayIconHandlerWin::~TrayIconHandlerWin()
{
    ids.erase(id);
    if (!notifyData.hWnd) {
        return;
    }
    Shell_NotifyIcon(NIM_DELETE, &notifyData);
}

TrayIconHandlerWin::TrayIconHandlerWin(TrayIconHandlerWin&& other) noexcept : TrayIconHandler(other.iconMapper)
{
    id = other.id;
    notifyData = other.notifyData;
    other.notifyData = {};
}

TrayIconHandlerWin& TrayIconHandlerWin::operator=(TrayIconHandlerWin&& other) noexcept
{
    if (this == &other) {
        return *this;
    }
    Shell_NotifyIcon(NIM_DELETE, &notifyData);
    id = other.id;
    notifyData.hWnd = other.notifyData.hWnd;
    notifyData = other.notifyData;
    other.notifyData.hWnd = nullptr;
    return *this;
}

void TrayIconHandlerWin::setIconByName(Protocol::IconName iconName)
{
    setShellNotifyIcon(loadIconFromResource(iconName));
}

void TrayIconHandlerWin::setIconByPath(const std::string& path)
{
    setShellNotifyIcon(loadIconFromFile(path));
}

void TrayIconHandlerWin::setShellNotifyIcon(HICON hIcon)
{
    if (!hIcon) {
        Utils::debug("Can't set shell notify icon");
        Utils::debug("Last error: ", GetLastError());
        return;
    }
    notifyData.hIcon = hIcon;
    Shell_NotifyIcon(NIM_MODIFY, &notifyData);
}

HICON TrayIconHandlerWin::loadIconFromResource(Protocol::IconName iconName)
{
    auto iconId = iconNameToId(iconName);
    if (iconId == -1) {
        return nullptr;
    }
    return static_cast<HICON>(LoadImage(HeadlessAppWin::getHInstance(),
        MAKEINTRESOURCE(iconId), IMAGE_ICON,
        0,
        0, 0));
}

HICON TrayIconHandlerWin::loadIconFromFile(const std::string& path)
{
    return static_cast<HICON>(LoadImage(
        nullptr,             
        path.c_str(),  
        IMAGE_ICON,
        0,              
        0,                
        LR_LOADFROMFILE |  
        LR_DEFAULTSIZE |
        LR_SHARED        
    ));
}

UINT TrayIconHandlerWin::getNewId()
{
    std::uniform_int_distribution<UINT> distribution(0, (std::numeric_limits<UINT>::max)());
    UINT result;
    do
    {
        result = distribution(generator);
    } while (ids.find(result) != ids.end());
    ids.insert(result);
    return result;
}
