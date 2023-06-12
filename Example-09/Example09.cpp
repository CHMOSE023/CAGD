/*
* ֪ʶ�� 9
* ��ά�任 ƽ�ơ���������ת�����䡢�ʹ���������ʽ
*/
#include "MainWindow.hpp"

#include "Brick.h"
#include "Transform2.h"



LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Brick       brick[9];           // ��ש����
    Transform2  transform[9];       // �任����
    P2          centerPoint[9];     // ���ĵ�
    double      rotationAngle[9];   // ��ת�Ƕ�
    static bool bPlay = true;       // ѡ��
    int         a = 200;

    centerPoint[0] = P2(0.0, 0.0);
    rotationAngle[0] = 0;

    centerPoint[1] = P2(-a, -a);
    rotationAngle[1] = 0;

    centerPoint[2] = P2(0, -a);
    rotationAngle[2] = 90;

    centerPoint[3] = P2(a, -a);
    rotationAngle[3] = 0;

    centerPoint[4] = P2(a, 0);
    rotationAngle[4] = 0;

    centerPoint[5] = P2(a, a);
    rotationAngle[5] = 0;

    centerPoint[6] = P2(0, a);
    rotationAngle[6] = 90;

    centerPoint[7] = P2(-a, a);
    rotationAngle[7] = 0;

    centerPoint[8] = P2(-a, 0);
    rotationAngle[8] = 90;

    for (int i = 0; i < 9; i++)
    {
        brick[i].ReadPoint();
        transform[i].SetMatrix(brick[i].P, 4);
        transform[i].Scale(a, a);
        transform[i].Rotate(rotationAngle[i]);
        transform[i].Translate(centerPoint[i].x, centerPoint[i].y);
    }

    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_LBUTTONDOWN:
        bPlay = !bPlay;
        InvalidateRect(m_hwnd, NULL, true); // ���� WM_PAINT
        return 0;

    case WM_PAINT:
    {       
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        RECT rect;
        GetClientRect(m_hwnd,&rect);

        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;

        SetMapMode(hdc, MM_ANISOTROPIC);
        SetWindowExtEx(hdc, width, height, NULL);
        SetViewportExtEx(hdc, width, height, NULL);
        SetViewportOrgEx(hdc, width / 2, height / 2,NULL);

        // �����ƴ���

        if (!bPlay)
        {
            brick[0].Draw(hdc);

        }
        else
        {
            for (int i = 0; i < 9; i++)
            {
                brick[i].Draw(hdc);
            }
        }        

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

    if (!win.Create(L"֪ʶ��9����ά���α任(������ש)", WS_OVERLAPPEDWINDOW))
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

