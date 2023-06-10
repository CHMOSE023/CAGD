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

            // �����ƴ���      
            // DrawLine(hdc);

            EndPaint(m_hwnd, &ps);
        }
        return 0;
        case WM_LBUTTONDOWN:
        {
            swprintf_s(m_str, L"Unit01-2 ���꣨X:%d,Y:%d)   ̧����ɻ��� ", LOWORD(lParam), HIWORD(lParam));   // ��ʽ���ַ���    

            m_pt1.x = LOWORD(lParam);          // ��ǰ���xλ��
            m_pt1.y = HIWORD(lParam);          // ��ǰ���yλ��

            SetWindowText(m_hwnd, m_str);      // ���ô��ڱ���
        }
        return 0;
        case WM_LBUTTONUP:
        {
            swprintf_s(m_str, L"Unit01-2 ���꣨X:%d,Y:%d��", LOWORD(lParam), HIWORD(lParam));

            HDC hdc = GetDC(m_hwnd);
            m_pt2.x = LOWORD(lParam);
            m_pt2.y = HIWORD(lParam);

            Drew(hdc, m_pt1, m_pt2);    // ����ֱ��

            ReleaseDC(m_hwnd, hdc);

            SetWindowText(m_hwnd, m_str);
        }

        return 0;

        default:
            return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        }
        return TRUE;

	};

    // ���г���
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
	// ����ֱ��
	void Draw(HDC hdc)
	{
		MoveToEx(hdc, 100, 100, NULL);
		LineTo(hdc, 500, 100);
	}

	// �������ֱ��
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

