#include "MainWindow.h"
#include "CubicBezierCurve.h"
#include "P2.h"
void MainWindow::DrawObject(HDC hdc) 
{
    CubicBezierCurve bzeier;
    P2 points[4];

    points[0].x = -400, points[0].y = -200;
    points[1].x = -200, points[1].y = 100;
    points[2].x = 200, points[2].y = 200;
    points[3].x = 300, points[3].y = -200;

    bzeier.ReadPoint(points);
    
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
        // ��������λ��
        RECT rect;
        GetClientRect(m_hwnd, &rect);

        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;

        SetMapMode(hdc, MM_ANISOTROPIC);
        SetWindowExtEx(hdc, width, height, NULL);
        SetViewportExtEx(hdc, width, -height, NULL);
        SetViewportOrgEx(hdc, width / 2, height / 2, NULL);

        // �����ƴ���
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

    if (!win.Create(L"֪ʶ��06�����ڻ�����������Bezier���߻����㷨", WS_OVERLAPPEDWINDOW))
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

