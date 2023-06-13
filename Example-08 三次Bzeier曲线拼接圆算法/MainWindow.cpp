#include "MainWindow.h"
#include "CubicBezierCurve.h"
#include "P2.h"
void MainWindow::DrawObject(HDC hdc) 
{
    CubicBezierCurve bzeier;
    P2 points[13];
    double r = 300;
    double m = 0.5523;

    points[0].x =r,       points[0].y =0.0;
    points[1].x = r,      points[1].y = r * m;
    points[2].x = r * m,  points[2].y = r;
    points[3].x = 0.0,    points[3].y = r;  
    points[4].x = -r * m, points[4].y = r;
    points[5].x = -r,     points[5].y = r * m;
    points[6].x = -r,     points[6].y = 0;
    points[7].x = -r,     points[7].y = -r * m;
    points[8].x = -r * m, points[8].y = -r;
    points[9].x = 0.0,    points[9].y = -r;
    points[10].x = r * m, points[10].y = -r;
    points[11].x = r,     points[11].y = -r * m;
    points[12].x = r,     points[12].y = 0.0;


    bzeier.ReadPoint(points);    
    bzeier.Draw(hdc);
    bzeier.DrawControlPolygon(hdc);

    bzeier.ReadPoint(points+3);
    bzeier.Draw(hdc);
    bzeier.DrawControlPolygon(hdc);

    bzeier.ReadPoint(points + 6);
    bzeier.Draw(hdc);
    bzeier.DrawControlPolygon(hdc);

    bzeier.ReadPoint(points + 9);
    bzeier.Draw(hdc);
    bzeier.DrawControlPolygon(hdc);
   
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

        // ！绘制代码
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

    if (!win.Create(L"知识点08：三次Bzeier曲线拼接圆算法", WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }

    ShowWindow(win.Window(), nCmdShow);
 
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

