#pragma once
#include "Windows.h"
#include "HeadlessApp.h"

class HeadlessAppWin :
    public HeadlessApp
{
public:
    HeadlessAppWin();
    ~HeadlessAppWin();
    HeadlessAppWin(HeadlessAppWin&& other) noexcept;
    HeadlessAppWin& operator = (HeadlessAppWin&& other) noexcept;

    static void setHInstance( HINSTANCE hInstance_ );
    static HINSTANCE getHInstance();

    HWND getHWnd() const;
private:
    HWND initWindow() const;
    void regClass() const;
    static LRESULT CALLBACK handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    std::shared_ptr<NamedPipe> makePipe(const std::string& name, NamedPipe::PipeType type) override;
    HWND hWnd{ nullptr };
    static HINSTANCE hInstance;
};

