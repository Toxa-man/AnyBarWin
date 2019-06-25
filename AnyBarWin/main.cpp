#include "HeadlessAppWin.h"
#include <thread>
#include "Utils.h"
#include "TrayIconHandlerWin.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    HeadlessAppWin::setHInstance(hInstance);
    std::unique_ptr<HeadlessApp> app = std::make_unique<HeadlessAppWin>();
    app->startEventLoop();
    return 0;

}
