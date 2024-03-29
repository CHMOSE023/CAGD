#include "MainWindow.h"
#include "Bezier.h"
// 绘制图元
void MainWindow::DrawObject(HDC hdc)
{
    P2 points[7];
   
    points[0].x = -400, points[0].y = -200;
    points[1].x = -200, points[1].y = 100;
    points[2].x = 200, points[2].y = 200;
    points[3].x = 300, points[3].y = -200;
    points[4].x = 350, points[4].y = 200;
    points[5].x = 400, points[5].y = -400;
    points[6].x = 450, points[6].y = -350;
 
    Bezier bezier;
    bezier.ReadPoint(points,6);


    HPEN  hpen1, hpen2, hpenOld;
    HBRUSH brush, brushOld;

    hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    hpen2 = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    hpenOld = (HPEN)SelectObject(hdc, hpen1);

    // 绘制曲线
    bezier.Draw(hdc);


    brush = CreateSolidBrush(RGB(0, 0, 255));
    brushOld = (HBRUSH)SelectObject(hdc, brush);
    SelectObject(hdc, hpen2);


    bezier.DrawControlPolygon(hdc);

    SelectObject(hdc, hpenOld);
    SelectObject(hdc, brushOld);

    DeleteObject(brush);
    DeleteObject(hpen1);
    DeleteObject(hpen2);
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

        // 调整坐标位置
        RECT rect;
        GetClientRect(m_hwnd, &rect);

        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;

        SetMapMode(hdc, MM_ANISOTROPIC);
        SetWindowExtEx(hdc, width, height, NULL);
        SetViewportExtEx(hdc, width, -height, NULL);
        SetViewportOrgEx(hdc, width / 2, height / 2, NULL);
        // ！绘制图形
        //MoveToEx(hdc, 100, 100, NULL);
        //LineTo(hdc, 300, 300);
        DrawObject(hdc);

        EndPaint(m_hwnd, &ps);
    }
    return 0;
    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR pCmdLine, int nCmdShow)
{
    MainWindow win;

    if (!win.Create(L"知识点05：Bezier曲线deCasteljau算法", WS_OVERLAPPEDWINDOW))
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

