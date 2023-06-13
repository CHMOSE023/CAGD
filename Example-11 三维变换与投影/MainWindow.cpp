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
   
    // WM_PAINT ��Ϣ
    InvalidateRect(m_hwnd, NULL, false); // false ���ػ�

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

    if (!win.Create(L"֪ʶ��11����ά�任��ͶӰ", WS_OVERLAPPEDWINDOW))
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

