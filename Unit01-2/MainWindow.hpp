#pragma once
#include "BaseWindow.hpp"

class MainWindow : public BaseWindow<MainWindow>
{
public:
    PCWSTR  ClassName() const { return L"Unit01-1 MainWindow"; }

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hwnd, &ps);
            // £¡»æÖÆ´úÂë


            EndPaint(m_hwnd, &ps);
        }
        return 0;

        default:
            return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        }
        return TRUE;
    }

    int OnRun(int nCmdShow)
    {
        if (!Create(L"Unit01-1 MainWindow", WS_OVERLAPPEDWINDOW))
        {
            return 0;
        }

        ShowWindow(Window(), nCmdShow);

        // Run the message loop.
        MSG msg = { };
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    };
};
