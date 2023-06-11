#pragma once
#include "P2D.h"
#include "BaseWindow.hpp"

class BezierCurve :public BaseWindow<BezierCurve>
{
public:
	BezierCurve() {};
	~BezierCurve() {};

	// 读取点
	void ReadPoint(P2D* p) 
	{
		for (int i = 0; i < 4; i++)
		{
			P[i] = p[i];
		}
	};

	// 绘制曲线
	void DrawCurve(HDC hdc)// de Casteljau 递推算法
	{
		P2D p01, p11, p21, p02, p12, p03;
		p01 = P[0], p11 = P[1], p21 = P[2], p03 = P[3];
		double tStep = 0.05;
		MoveToEx(hdc, ROUND(P[0].X), ROUND(P[0].Y), NULL);
		for (double t1 = 0; t1 < 1; t1 += tStep)
		{
			// 一次递推
			p01 = (1 - t1) * P[0] + t1 * P[1];
			p11 = (1 - t1) * P[1] + t1 * P[2];
			p21 = (1 - t1) * P[2] + t1 * P[3];

			// 二次递推
			p02 = (1 - t1) * p01 + t1 * p11;
			p12 = (1 - t1) * p11 + t1 * p21;

			// 三次递推 曲线点
			p03 = (1 - t1) * p02 + t1 * p12;

			LineTo(hdc, ROUND(p03.X), ROUND(p03.Y));
		}

		LineTo(hdc, ROUND(P[3].X), ROUND(P[3].Y));

	};

	// 绘制控制点
	void DrawPolygon(HDC hdc) 
	{
		for (int i = 0; i < 4; i++)
		{
			// 绘制圆
			Ellipse(hdc, ROUND(P[i].X) - 5, ROUND(P[i].Y) - 5, ROUND(P[i].X) + 5, ROUND(P[i].Y) + 5);

			// 绘制线
			if (0 == i)
			{
				MoveToEx(hdc, ROUND(P[i].X), ROUND(P[i].Y), NULL);
			}
			else
			{
				LineTo(hdc, ROUND(P[i].X), ROUND(P[i].Y));
			}
		}

	};


	PCWSTR  ClassName() const {	return L"BezierCurve";};
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
			//RECT rect;

			HPEN  hpen1, hpen2, hpenOld;
			HBRUSH brush, brushOld;

			hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			hpen2 = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			hpenOld = (HPEN)SelectObject(hdc, hpen1);


			DrawCurve(hdc); // ！曲线     


			brush = CreateSolidBrush(RGB(0, 0, 255));
			brushOld = (HBRUSH)SelectObject(hdc, brush);
			SelectObject(hdc, hpen2);

			DrawPolygon(hdc); // ！控制线     

			EndPaint(m_hwnd, &ps);


			SelectObject(hdc, hpenOld);
			SelectObject(hdc, brushOld);

			DeleteObject(brush);
			DeleteObject(hpen1);
			DeleteObject(hpen2);
		}
		return 0;

		default:
			return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
		}
		return TRUE;
	}
	;
	int     OnRun(int nCmdShow)
	{
		if (!Create(L"BezierCurve", WS_OVERLAPPEDWINDOW))
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

		return 0;
	};
private:
	P2D P[4];
};


