/*
* 拼接四段三次bazier曲线拼接圆
*/
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


	PCWSTR  ClassName() const { return L"BezierCurve"; };
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
	

		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
		{
			double r = 200.0;
			double m = 0.5523;
			// 曲线控制点
			P2D p[12] = {
				/* 0*/	{r,0},
				/* 1*/ 	{r,r * m},
				/* 2*/	{r * m,r},
				/* 3*/ 	{0,r},
				/* 4*/	{-r * m,r},
				/* 5*/ 	{-r,m * r},
				/* 6*/ 	{-r,0},
				/* 7*/	{-r,-r * m},
				/* 8*/	{-r * m,-r},
				/* 9*/	{0,-r},
				/*10*/	{r * m,-r},
				/*11*/	{r,-r * m}
			};


			PAINTSTRUCT ps;
			HDC   hdc = BeginPaint(m_hwnd, &ps);
			//RECT rect;

			HPEN  hpen1, hpen2, hpenOld;
			HBRUSH brush, brushOld;
		
			
			hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			hpen2 = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			hpenOld = (HPEN)SelectObject(hdc, hpen1);

			// 调整坐标系
			RECT rect;
			GetClientRect(m_hwnd, &rect);
			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;
			//SetMapMode(hdc,MM_ANISOTROPIC);
			SetWindowExtEx(hdc,width,height,NULL);
			SetViewportOrgEx(hdc, width / 2, height / 2, NULL);
			// MoveToEx(hdc, 0, 0, NULL);
			// LineTo(hdc, width, height);
			DrawCurve(hdc);
			  // 第1段
			  P[0] = p[0];
			  P[1] = p[1];
			  P[2] = p[2];
			  P[3] = p[3];
			  DrawCurve(hdc); // ！曲线     
			 
			 // 第2段
			 P[0] = p[3];
			 P[1] = p[4];
			 P[2] = p[5];
			 P[3] = p[6];
			 DrawCurve(hdc); // ！曲线     
			 
			 // 第3段
			 P[0] = p[6];
			 P[1] = p[7];
			 P[2] = p[8];
			 P[3] = p[9];
			 DrawCurve(hdc); // ！曲线     
			 
			 // 第4段
			 P[0] = p[9];
			 P[1] = p[10];
			 P[2] = p[11];
			 P[3] = p[0];
			 DrawCurve(hdc); // ！曲线    



			brush = CreateSolidBrush(RGB(0, 0, 255));
			brushOld = (HBRUSH)SelectObject(hdc, brush);
			SelectObject(hdc, hpen2);


			  // 第1段
			  P[0] = p[0];
			  P[1] = p[1];
			  P[2] = p[2];
			  P[3] = p[3];
			  DrawPolygon(hdc); // ！控制线     
			  
			  // 第2段
			  P[0] = p[3];
			  P[1] = p[4];
			  P[2] = p[5];
			  P[3] = p[6];
			  DrawPolygon(hdc); // ！控制线     
			  
			  // 第3段
			  P[0] = p[6];
			  P[1] = p[7];
			  P[2] = p[8];
			  P[3] = p[9];
			  DrawPolygon(hdc); // ！控制线     
			  
			  // 第4段
			  P[0] = p[9];
			  P[1] = p[10];
			  P[2] = p[11];
			  P[3] = p[0];			
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


