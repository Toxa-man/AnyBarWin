#include "HeadlessAppWin.h"
#include <string>
#include "TrayIconHandlerWin.h"


HeadlessAppWin::HeadlessAppWin() :
    hWnd{ initWindow() }

{
    iconHandler = std::make_unique<TrayIconHandlerWin>(hWnd);
    regClass();
}


HeadlessAppWin::~HeadlessAppWin()
{
}

void HeadlessAppWin::startEventLoop()
{
}

HWND HeadlessAppWin::initWindow()
{
    auto hWnd = CreateWindow("main_class", "", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        OutputDebugString("Can't create window\n");
        OutputDebugString("Last error: ");
        OutputDebugString(std::to_string(GetLastError()).c_str());
        ExitProcess(1);
    }
    return hWnd;
}
