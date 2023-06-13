#include "MainWindow.h"
#include "Ellipse.h"
#include "Transform2.h"
#include "P2.h"

bool m_bPlay = true;

void MainWindow::DrawObject(HDC hdc) 
{
    MoveToEx(hdc, -10, 0, NULL);
    LineTo(hdc, 10, 0);

    MoveToEx(hdc, 0, -10, NULL);
    LineTo(hdc, 0, 10);

    CAGD::Ellipse ellipse;
    Transform2 transform2;
    ellipse.ReadPoint();

    transform2.SetMatrix(ellipse.Points, 12);
    transform2.Scale(200, 100);
    
    static  int r = 5;

    if (m_bPlay)
    {
        transform2.Rotate(r += 1);      
        ellipse.Draw(hdc);
        m_bPlay = false;
    }
    else
    {
        ellipse.Draw(hdc);
    }  
    
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CREATE:
        SetTimer(m_hwnd, WM_TIMER, 100, NULL);
        return 0;

    case WM_TIMER:
        m_bPlay = true;
        InvalidateRect(m_hwnd, NULL, false);
        return 0;
        
    case WM_RBUTTONDOWN:
        m_bPlay = true;
        SetTimer(m_hwnd, WM_TIMER, 100, NULL);
        return 0;

    case WM_LBUTTONDOWN:       
        m_bPlay = false;
        KillTimer(m_hwnd, WM_TIMER);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);

        RECT rect;
        GetClientRect(m_hwnd, &rect);

        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;

        /* ˫����   1.���Ƶ��ڴ�dc��2.���ڴ�dc���Ƶ�����dc*/
        HDC  hMemDC = CreateCompatibleDC(hdc);                          // 1.���������ڴ�DC,��ʱ���Ĵ�Сʱ1X1����С�����ܻ���       
        HBITMAP hMemBmp = CreateCompatibleBitmap(hdc, width, height);   // 2.��������λͼ���ṩ�滭����      
        SelectObject(hMemDC, hMemBmp);                                  // 3.�Ѽ���λͼѡ�������ڴ�DC��,�˿�DC�Ĵ�С��λͼһ�£����Ի���        
        FillRect(hMemDC, &rect, (HBRUSH)(GetBkColor(hdc)));             // 4.�����ڴ汳�� COLOR_WINDOW+1  GetBkColor(hdc)

        // ����hdc����
        SetMapMode(hdc, MM_ANISOTROPIC);
        SetWindowExtEx(hdc, width, height, NULL);
        SetViewportExtEx(hdc, width, -height, NULL);
        SetViewportOrgEx(hdc, width / 2, height / 2, NULL);

        // ƫ��Rect
        OffsetRect(&rect, -width / 2, -height / 2);

        // ����hMemDC����
        SetMapMode(hMemDC, MM_ANISOTROPIC);
        SetWindowExtEx(hMemDC, width, height, NULL);
        SetViewportExtEx(hMemDC, width, -height, NULL);
        SetViewportOrgEx(hMemDC, width / 2, height / 2, NULL);


        // ����ʼ��ͼ
        DrawObject(hMemDC);


        // 5.���ڴ�DC�е�ͼ��һ���Ի�������DC��    
        BitBlt(hdc, rect.left, rect.top, width, height, hMemDC, -width / 2, -height / 2, SRCCOPY);

        DeleteDC(hMemDC);  // �ͷ���Դ
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

    if (!win.Create(L"֪ʶ��10��˫���嶯������", WS_OVERLAPPEDWINDOW | CS_DBLCLKS))
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

