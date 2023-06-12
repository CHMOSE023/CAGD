#include "MainWindow.hpp"

POINT m_pt1;   // ��1��
POINT m_pt2;   // ��2��

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
        // ��������

        EndPaint(m_hwnd, &ps);
    }
    return 0;
    case WM_LBUTTONDOWN: // ��갴��
    {
        
        m_pt1.x = LOWORD(lParam);          // x����
        m_pt1.y = HIWORD(lParam);          // y����       
    }
    return 0;
    case WM_LBUTTONUP:  // ���̧��
    {       
        HDC hdc = GetDC(m_hwnd);

        m_pt2.x = LOWORD(lParam);
        m_pt2.y = HIWORD(lParam);
       
        MoveToEx(hdc, m_pt1.x, m_pt1.y, NULL);   // ���ƶ���P01��
        LineTo(hdc, m_pt2.x, m_pt2.y );          // ������ֱ��

        ReleaseDC(m_hwnd, hdc);       
    }
    return 0;
    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    MainWindow win;

    if (!win.Create(L"֪ʶ��04��Bezier���߶����㷨", WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }

    ShowWindow(win.Window(), nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

