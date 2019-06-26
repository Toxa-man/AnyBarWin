#include "HeadlessAppWin.h"
#include <thread>
#include "Utils.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    CreateMutex(nullptr,
        TRUE,
        TEXT("InstanceGuardMutex"));
    switch (GetLastError()) {
    case ERROR_SUCCESS:
        break;
    case ERROR_ALREADY_EXISTS:
        Utils::debug("Server instance is already running");
        return -1;
    default:
        Utils::debug("Error occured while obtaining mutex");
        Utils::debug("Last error: ", GetLastError());
        break;
    }

    HeadlessAppWin::setHInstance(hInstance);
    std::unique_ptr<HeadlessApp> app = std::make_unique<HeadlessAppWin>();
    app->startEventLoop();
    return 0;

}
