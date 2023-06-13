#include "MainWindow.h"
#include "Cube.h"
#include "P3.h"
#include "Transform3.h"

void MainWindow::DrawObject(HDC hdc) 
{
    Cube cube;
    Transform3 transform3;
    double scale = 300.0;
   
    cube.ReadVertex();
    cube.ReadFacet();

    transform3.SetMatrix(cube.GetPoints(), 8);

    transform3.Scale(scale, scale, scale);

    transform3.Translate(-scale/2, -scale / 2, -scale / 2);

    static  int alpha = 5, bate = 5;

    transform3.RotateX(alpha++);
    transform3.RotateY(bate++);

    cube.Draw(hdc);
   
    // WM_PAINT 消息
    InvalidateRect(m_hwnd, NULL, false); // false 不重绘

    Sleep(1);
    
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

        /* 双缓冲   1.绘制到内存dc，2.从内存dc复制到窗口dc*/
        HDC  hMemDC = CreateCompatibleDC(hdc);                          // 1.创建兼容内存DC,此时它的大小时1X1，很小，不能绘制       
        HBITMAP hMemBmp = CreateCompatibleBitmap(hdc, width, height);   // 2.创建兼容位图，提供绘画区域      
        SelectObject(hMemDC, hMemBmp);                                  // 3.把兼容位图选到兼容内存DC中,此刻DC的大小与位图一致，可以绘制        
        FillRect(hMemDC, &rect, (HBRUSH)(GetBkColor(hdc)));             // 4.设置内存背景 COLOR_WINDOW+1  GetBkColor(hdc)

        // 调整hdc坐标
        SetMapMode(hdc, MM_ANISOTROPIC);
        SetWindowExtEx(hdc, width, height, NULL);
        SetViewportExtEx(hdc, width, -height, NULL);
        SetViewportOrgEx(hdc, width / 2, height / 2, NULL);

        // 偏移Rect
        OffsetRect(&rect, -width / 2, -height / 2);

        // 调整hMemDC坐标
        SetMapMode(hMemDC, MM_ANISOTROPIC);
        SetWindowExtEx(hMemDC, width, height, NULL);
        SetViewportExtEx(hMemDC, width, -height, NULL);
        SetViewportOrgEx(hMemDC, width / 2, height / 2, NULL);


        // ！开始绘图
        DrawObject(hMemDC);


        // 5.把内存DC中的图像一次性画到窗口DC上    
        BitBlt(hdc, rect.left, rect.top, width, height, hMemDC, -width / 2, -height / 2, SRCCOPY);

        DeleteDC(hMemDC);  // 释放资源
        DeleteObject(hMemBmp);

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

    if (!win.Create(L"知识点11：三维变换与投影", WS_OVERLAPPEDWINDOW))
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

