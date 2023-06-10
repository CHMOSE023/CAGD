#pragma once
#include <stdio.h>
#include <vector>
#include "BaseWindow.hpp"
#include "P2D.h"

using std::vector;

class  Bezier :public BaseWindow <Bezier>
{
public:
	Bezier();
	virtual ~Bezier();

	void ReadPoint(P2D* p2ds, int n);

	void Draw(HDC hdc);

	void DrawControlPolygon(HDC hdc);

	
	PCWSTR  ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int     OnRun(int nCmdShow);

private:
	double Cni(const int& n, const int& i);
	int Factorial(int n);//计算阶乘

public:
	vector<P2D> P2ds;
	int N;
};

Bezier::Bezier() {};
Bezier::~Bezier() {};

PCWSTR Bezier::ClassName()const
{
	return L"Bezier";
}

LRESULT Bezier::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		RECT rect;

		HPEN  hpen1, hpen2, hpenOld;
		HBRUSH brush, brushOld;

		hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hpen2 = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		hpenOld = (HPEN)SelectObject(hdc, hpen1);

		
		Draw(hdc); // ！曲线     


		brush = CreateSolidBrush(RGB(0, 0, 255));
		brushOld = (HBRUSH)SelectObject(hdc, brush);
		SelectObject(hdc, hpen2);

		DrawControlPolygon(hdc); // ！控制线     

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

int Bezier::OnRun(int nCmdShow)
{
	if (!Create(L"Bezier", WS_OVERLAPPEDWINDOW))
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
}


void Bezier::ReadPoint(P2D* p2ds, int n)
{
	N = n;
	for (size_t i = 0; i < n; i++)
	{
		P2ds.push_back(p2ds[i]);
	}
}

void Bezier::Draw(HDC hdc) 
{
	MoveToEx(hdc, ROUND(P2ds[0].X), ROUND(P2ds[0].Y),NULL);
	double tStep = 0.01;
	for (double t = 0; t < 1.0; t +=tStep)
	{
		double x = 0.0, y = 0.0;
		for (size_t i = 0; i < N+1; i++)
		{
			x += P2ds[i].X * Cni(N, i) * pow(t, i) * pow(1 - t, N - i); //pow 幂函数
			y += P2ds[i].Y * Cni(N, i) * pow(t, i) * pow(1 - t, N - i);
		}
		LineTo(hdc, ROUND(x), ROUND(y));
	}
}

void Bezier::DrawControlPolygon(HDC hdc) 
{
	for (int i = 0; i < N + 1; i++)
	{	
		// 绘制圆
		Ellipse(hdc, ROUND(P2ds[i].X) - 5, ROUND(P2ds[i].Y) - 5, ROUND(P2ds[i].X) + 5, ROUND(P2ds[i].Y) + 5);

		// 绘制线
		if (0 == i)
		{
			MoveToEx(hdc, ROUND(P2ds[i].X), ROUND(P2ds[i].Y), NULL);
		}
		else
		{
			LineTo(hdc, ROUND(P2ds[i].X), ROUND(P2ds[i].Y));	
		}	
	}
}

int Bezier::Factorial(int n)
{
	int factorial;

	if (n == 0 || n == 1)
	{
		factorial = 1;
	}
	else
	{
		factorial = n * Factorial(n - 1);
	}

	return factorial;
}

double Bezier::Cni(const int& n, const int& i) 
{
	return double(Factorial(n)) / (Factorial(i) * Factorial(n - i));
}