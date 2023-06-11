#pragma once
#include <stdio.h>
#include <vector>
#include "BaseWindow.hpp"
#include "P2D.h"

class BezierDeCasteljau :public BaseWindow<BezierDeCasteljau>
{
public:
	BezierDeCasteljau();
	~BezierDeCasteljau();

	void ReadPoint(P2D* p, int n);
	void Draw(HDC hdc);
	void DrawControlPolygon(HDC hdc);

	PCWSTR  ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	int     OnRun(int nCmdShow);

private:
	void DeCasteljag(double t);// deCateljau�㷨
public:
	P2D       Points[8];	// ���Ƶ�
	P2D       P2P[8][8];  // ���ƶ�ά����
	//vector<vector<int>> matrix{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	int N = 0;		// ���ߴ���
};



BezierDeCasteljau::BezierDeCasteljau()
{

}

BezierDeCasteljau::~BezierDeCasteljau()
{
}


PCWSTR BezierDeCasteljau::ClassName()const
{
	return L"BezierDeCasteljau";
}

LRESULT BezierDeCasteljau::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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


		Draw(hdc); // ������     


		brush = CreateSolidBrush(RGB(0, 0, 255));
		brushOld = (HBRUSH)SelectObject(hdc, brush);
		SelectObject(hdc, hpen2);

		DrawControlPolygon(hdc); // ��������     

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

int BezierDeCasteljau::OnRun(int nCmdShow)
{
	if (!Create(L"BezierDeCasteljau", WS_OVERLAPPEDWINDOW))
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

void BezierDeCasteljau::ReadPoint(P2D* points, int n)
{
	
	N = n;
	for (size_t i = 0; i < n; i++)
	{
		Points[i] = points[i];
	}
}
void BezierDeCasteljau::Draw(HDC hdc)
{
	MoveToEx(hdc, ROUND(Points[0].X), ROUND(Points[0].Y), NULL);
	double tStep = 0.03; // ����
	for (double t = 0.0; t <= 1.0; t += tStep)
	{
		DeCasteljag(t);
		LineTo(hdc, ROUND(P2P[0][N].X), ROUND(P2P[0][N].Y));
	}
}

void BezierDeCasteljau::DeCasteljag(double t)
{
	
	for (int k = 0; k <= N; k++)
	{
		P2P[k][0].X = Points[k].X;   // ���Ƶ�һά���鸳ֵ����ά
		P2P[k][0].Y = Points[k].Y;
	}

	for (int r = 1; r <= N; r++)  // DeCasteljag ���ƹ�ʽ��ʹ�ö�ά����
	{
		for (int i = 0; i <= (N - r); i++)
		{
			P2P[i][r] = (1 - t) * P2P[i][r - 1] + t * P2P[i + 1][r - 1]; // ���ƹ�ʽ
		}
	}
}

void BezierDeCasteljau::DrawControlPolygon(HDC hdc)  // ���ƿ��ƶ����
{

	for (int i = 0; i < N + 1; i++)
	{
		// ����Բ
		Ellipse(hdc, ROUND(Points[i].X) - 5, ROUND(Points[i].Y) - 5, ROUND(Points[i].X) + 5, ROUND(Points[i].Y) + 5);

		// ������
		if (0 == i)
		{
			MoveToEx(hdc, ROUND(Points[i].X), ROUND(Points[i].Y), NULL);
		}
		else
		{
			LineTo(hdc, ROUND(Points[i].X), ROUND(Points[i].Y));
		}
	}

}