#pragma once
#include "Windows.h"
#include "TrayIconHandler.h"
#include <set>
#include <random>

/**
 * \brief Represents Windows-specific tray handler
 */
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
    /**
     * \brief Loads icon from resources using mapper from base class to determine id
     * \param iconName 
     * \return handle to icon
     */
    HICON loadIcon(const std::string& iconName);
    /**
     * \brief Generates unique id for each class instance
     * \return generated id
     */
    static UINT getNewId();
    static std::mt19937 generator;
    /**
     * \brief unique id of that icon handler instance
     */
    UINT id = 0;
    /**
     * \brief Contains all handlers' id
     */
    static std::set<UINT> ids;
    NOTIFYICONDATA notifyData {};
};

