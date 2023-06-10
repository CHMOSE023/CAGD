#pragma once
#include "BaseWindow.hpp"
#include <stdio.h>

class TestLine : public BaseWindow<TestLine>
{
public:
	PCWSTR  ClassName() const { return L"Unit01-2 DrewLine"; }

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
            HDC   hdc = BeginPaint(m_hwnd, &ps);

            // ！绘制代码      
            // DrawLine(hdc);

            EndPaint(m_hwnd, &ps);
        }
        return 0;
        case WM_LBUTTONDOWN:
        {
            swprintf_s(m_str, L"Unit01-2 坐标（X:%d,Y:%d)   抬起完成绘制 ", LOWORD(lParam), HIWORD(lParam));   // 格式化字符串    

            m_pt1.x = LOWORD(lParam);          // 当前鼠标x位置
            m_pt1.y = HIWORD(lParam);          // 当前鼠标y位置

            SetWindowText(m_hwnd, m_str);      // 设置窗口标题
        }
        return 0;
        case WM_LBUTTONUP:
        {
            swprintf_s(m_str, L"Unit01-2 坐标（X:%d,Y:%d）", LOWORD(lParam), HIWORD(lParam));

            HDC hdc = GetDC(m_hwnd);
            m_pt2.x = LOWORD(lParam);
            m_pt2.y = HIWORD(lParam);

            Drew(hdc, m_pt1, m_pt2);    // 绘制直线

            ReleaseDC(m_hwnd, hdc);

            SetWindowText(m_hwnd, m_str);
        }

        return 0;

        default:
            return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        }
        return TRUE;

	};

    // 运行程序
    int OnRun(int nCmdShow)
    {
        if (!Create(L"Unit01-2 DrewLine", WS_OVERLAPPEDWINDOW))
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

public:
	// 绘制直线
	void Draw(HDC hdc)
	{
		MoveToEx(hdc, 100, 100, NULL);
		LineTo(hdc, 500, 100);
	}

	// 两点绘制直线
	void Drew(HDC hdc, POINT pt1, POINT pt2)
	{
		MoveToEx(hdc, pt1.x, pt1.y, NULL);

		LineTo(hdc, pt2.x, pt2.y);
	}

   
	
private:
	POINT m_pt1;
	POINT m_pt2;

    wchar_t m_str[256] = { 0 };
};

