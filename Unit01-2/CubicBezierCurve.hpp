#pragma once
#include "BaseWindow.hpp"
#include <stdio.h>
#include "P2D.h"

class CubicBezierCurve :public BaseWindow<CubicBezierCurve>
{
public:
	CubicBezierCurve() {};
	~CubicBezierCurve() {};

public:
	void    ReadPoint(P2D* p);
	void    Draw(HDC hdc);
	void    DrawControlPolygon(HDC hdc);

	int     OnRun(int nCmdShow);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	PCWSTR  ClassName()const;

public:
	P2D  m_p2d[4];
};


PCWSTR CubicBezierCurve::ClassName()const
{
	return L"CubicBezierCurve";
}

LRESULT CubicBezierCurve::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		//RECT  rect;

		// ！绘制代码      
		Draw(hdc);
		DrawControlPolygon(hdc);

		EndPaint(m_hwnd, &ps);
	}
	return 0;

	default:
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
	return TRUE;
}

int CubicBezierCurve::OnRun(int nCmdShow)
{
	if (!Create(L"CubicBezierCurve", WS_OVERLAPPEDWINDOW))
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
}

void CubicBezierCurve::ReadPoint(P2D* p2d)
{
	for (size_t i = 0; i < 4; i++)
	{
		m_p2d[i] = p2d[i];
	}
}

void CubicBezierCurve::Draw(HDC hdc)            // 绘制曲线
{
	HPEN  hpen, hpenOld;
	hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	hpenOld = (HPEN)SelectObject(hdc, hpen);

	MoveToEx(hdc, ROUND(m_p2d[0].X), ROUND(m_p2d[0].Y), NULL);

	double tStep = 0.01;

	for (double t = 0; t < 1.0; t += tStep)
	{
		P2D p(0, 0);

		// 伯恩斯坦函数
		double bern03 = (1 - t) * (1 - t) * (1 - t);
		double bern13 = 3 * t * (1 - t) * (1 - t);
		double bern23 = 3 * t * t * (1 - t);
		double bern33 = t * t * t;

		p += bern03 * m_p2d[0] + bern13 * m_p2d[1] + bern23 * m_p2d[2] + bern33 * m_p2d[3];

		LineTo(hdc, ROUND(p.X), ROUND(p.Y));
	}

	SelectObject(hdc, hpenOld);
	DeleteObject(hpen);
}

void CubicBezierCurve::DrawControlPolygon(HDC hdc)  // 辅助线
{
	HPEN  hpen, hpenOld;
	HBRUSH brush, brushOld;

	hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hpenOld = (HPEN)SelectObject(hdc, hpen);

	brush = CreateSolidBrush(RGB(0, 0, 255));
	brushOld = (HBRUSH)SelectObject(hdc, brush);

	for (size_t i = 0; i < 4; i++)
	{
		if (0 == i)
		{
			MoveToEx(hdc, ROUND(m_p2d[i].X), ROUND(m_p2d[i].Y), NULL);
			Ellipse(hdc, ROUND(m_p2d[i].X) - 5, ROUND(m_p2d[i].Y) - 5, ROUND(m_p2d[i].X) + 5, ROUND(m_p2d[i].Y) + 5);
		}
		else
		{
			LineTo(hdc, ROUND(m_p2d[i].X), ROUND(m_p2d[i].Y));
			Ellipse(hdc, ROUND(m_p2d[i].X) - 5, ROUND(m_p2d[i].Y) - 5, ROUND(m_p2d[i].X) + 5, ROUND(m_p2d[i].Y) + 5);
		}

	}

	SelectObject(hdc, hpenOld);
	SelectObject(hdc, brushOld);

	DeleteObject(brush);
	DeleteObject(hpen);
}