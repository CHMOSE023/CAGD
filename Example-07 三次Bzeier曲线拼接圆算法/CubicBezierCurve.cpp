#include "CubicBezierCurve.h"
CubicBezierCurve::CubicBezierCurve() { Points = nullptr; };
CubicBezierCurve::~CubicBezierCurve() { };

void CubicBezierCurve::ReadPoint(P2* points)
{
	Points = points;
}

void CubicBezierCurve::Draw(HDC hdc)
{
	HPEN  hPen , hPenOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, ROUND(Points[0].x), ROUND(Points[0].y), NULL);
	double tStep = 0.01;
	for (double t = 0.0; t <= 1.0; t+=tStep)
	{
		P2 point(0.0, 0.0); // 曲线上的点

		// 伯恩斯坦函数
		double bern03 = (1 - t) * (1 - t) * (1 - t);
		double bern13 = 3 * t * (1 - t) * (1 - t);
		double bern23 = 3 * t * t * (1 - t);
		double bern33 = t * t * t;

		point += bern03 * Points[0] + bern13 * Points[1] + bern23 * Points[2] + bern33 * Points[3];

		LineTo(hdc, ROUND(point.x), ROUND(point.y));
	}

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void CubicBezierCurve::DrawControlPolygon(HDC hdc) 
{
	HPEN  hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	HBRUSH hBrush, hBrushOld;
	hBrush= CreateSolidBrush(RGB(0, 0, 255));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, ROUND(Points[0].x-5), ROUND(Points[0].y-5), ROUND(Points[0].x+5), ROUND(Points[0].y + 5));
	MoveToEx(hdc, ROUND(Points[0].x), ROUND(Points[0].y), NULL);
	for (int i = 1; i < 4; i++)
	{
		Ellipse(hdc, ROUND(Points[i].x - 5), ROUND(Points[i].y - 5), ROUND(Points[i].x + 5), ROUND(Points[i].y + 5));
		LineTo(hdc, ROUND(Points[i].x), ROUND(Points[i].y));
	}


	SelectObject(hdc, hPenOld);
	SelectObject(hdc, hBrushOld);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

