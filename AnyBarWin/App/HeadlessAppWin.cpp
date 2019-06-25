#include "HeadlessAppWin.h"
#include "TrayIconHandlerWin.h"
#include "NamedPipeWin.h"
#include "../Utils.h"

HINSTANCE HeadlessAppWin::hInstance{ nullptr };


HeadlessAppWin::HeadlessAppWin() :
    hWnd{ initWindow() }

{
    iconHandler = std::make_unique<TrayIconHandlerWin>(hWnd);
}


HeadlessAppWin::~HeadlessAppWin()
{
    DestroyWindow(hWnd);
}

HeadlessAppWin::HeadlessAppWin(HeadlessAppWin&& other) noexcept
{
    hWnd = other.hWnd;
    iconHandler = std::move(other.iconHandler);
    other.hWnd = nullptr;
}

HeadlessAppWin& HeadlessAppWin::operator=(HeadlessAppWin&& other) noexcept
{
    if (this == &other) {
        return *this;
    }
    DestroyWindow(hWnd);
    hWnd = other.hWnd;
    other.hWnd = nullptr;
    iconHandler = std::move(other.iconHandler);
    return *this;
}

void HeadlessAppWin::setHInstance(HINSTANCE hInstance_)
{
    hInstance = hInstance_;
}

HINSTANCE HeadlessAppWin::getHInstance()
{
    return hInstance;
}

HWND HeadlessAppWin::getHWnd() const
{
    return hWnd;
}

HWND HeadlessAppWin::initWindow() const
{
    regClass();
    auto hWnd = CreateWindow("main_class", "", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        Utils::debug("Can't create window\n", "Last error: ", GetLastError());
        ExitProcess(1);
    }
    return hWnd;
}

void HeadlessAppWin::regClass() const
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = handleEvent;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "main_class";
    wcex.hIconSm = nullptr;

    RegisterClassEx(&wcex);
}

LRESULT HeadlessAppWin::handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

std::shared_ptr<NamedPipe> HeadlessAppWin::makePipe(const std::string& name, NamedPipe::PipeType type)
{
    return std::make_shared<NamedPipeWin>(name, type);
}
