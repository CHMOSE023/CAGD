#include "MainWindow.h"
#include"BicubicBezierPatch.h"

void MainWindow::DrawObject(HDC hdc)
{
    BicubicBezierPatch bbp;
    P3 pts[4][4];
    pts[0][0].x = 20;   pts[0][0].y = 0;   pts[0][0].z = 200;
    pts[0][1].x =  0;   pts[0][1].y = 100; pts[0][1].z = 150;
    pts[0][2].x = -130; pts[0][2].y = 100; pts[0][2].z = 50;
    pts[0][3].x = -250; pts[0][3].y = 50;  pts[0][3].z = 0;

    pts[1][0].x = 100;   pts[1][0].y = 100;   pts[1][0].z = 150;
    pts[1][1].x = 30;    pts[1][1].y = 100;   pts[1][1].z = 100;
    pts[1][2].x = -40;   pts[1][2].y = 100;   pts[1][2].z = 50;
    pts[1][3].x = -110;  pts[1][3].y = 100;   pts[1][3].z = 0;

    pts[2][0].x = 280;   pts[2][0].y = 90;    pts[2][0].z = 140;
    pts[2][1].x = 110;   pts[2][1].y = 120;   pts[2][1].z = 80;
    pts[2][2].x = 0;     pts[2][2].y = 130;   pts[2][2].z = 30;
    pts[2][3].x = -100;  pts[2][3].y = 150;   pts[2][3].z = -50;

    pts[3][0].x = 350;   pts[3][0].y = 30;   pts[3][0].z = 150;
    pts[3][1].x = 200;   pts[3][1].y = 150;   pts[3][1].z = 500;
    pts[3][2].x = 50;    pts[3][2].y = 200;   pts[3][2].z = 0;
    pts[3][3].x = 0;     pts[3][3].y = 100;   pts[3][3].z = -70;

    bbp.ReadControlPoint(pts);
    bbp.DrawCurvedPatch(hdc);
    bbp.DrawControlGrid(hdc);

  
}

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

        RECT rect;
        GetClientRect(m_hwnd, &rect);

        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;

        // 调整hdc坐标
        SetMapMode(hdc, MM_ANISOTROPIC);
        SetWindowExtEx(hdc, width, height, NULL);
        SetViewportExtEx(hdc, width, -height, NULL);
        SetViewportOrgEx(hdc, width / 2, height / 2, NULL);
        // ！绘制图形
        DrawObject(hdc);


        EndPaint(m_hwnd, &ps);
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

    if (!win.Create(L"知识点11：双三次Bezier曲面片定义", WS_OVERLAPPEDWINDOW))
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

