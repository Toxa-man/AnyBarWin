#pragma once
#include "Windows.h"
#include "HeadlessApp.h"
#include <memory>

class HeadlessAppWin :
    public HeadlessApp
{
public:
    HeadlessAppWin();
    void startEventLoop() override;
    static void setHInstance(const HINSTANCE hInstance);
    static HINSTANCE getHInstance();

    HWND getHWnd() const;
    ~HeadlessAppWin() = default;
private:
    HWND hWnd{ nullptr };
    inline static HINSTANCE hInstance{ nullptr };
    HWND initWindow();
    void regClass() const;
    static LRESULT CALLBACK handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    void namedPipeLoop();
    bool handleMessage(HANDLE hPipe);
    constexpr static std::size_t buffSize = 1024;
};

