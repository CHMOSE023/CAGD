#include "CubicBezierCurve.h"
CubicBezierCurve::CubicBezierCurve() { Points = nullptr; };
CubicBezierCurve::~CubicBezierCurve() { };

void CubicBezierCurve::ReadPoint(P2* points)
{
	Points = points;
}

void CubicBezierCurve::Draw(HDC hdc)
{
	HPEN  hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, ROUND(Points[0].x), ROUND(Points[0].y), NULL);
	double tStep = 0.01;
	for (double t = 0.0; t <= 1.0; t += tStep)
	{
		P2 p01, p11, p21;
		P2 p02, p12;
		P2 point;

		p01 = (1 - t) * Points[0] + t * Points[1];
		p11 = (1 - t) * Points[1] + t * Points[2];
		p21 = (1 - t) * Points[2] + t * Points[3];

		p02 = (1 - t) * p01 + t * p11;
		p12 = (1 - t) * p11 + t * p21;

		point = (1 - t) * p02 + t * p12;

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
	hBrush = CreateSolidBrush(RGB(0, 0, 255));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, ROUND(Points[0].x) - 5, ROUND(Points[0].y) - 5, ROUND(Points[0].x) + 5, ROUND(Points[0].y) + 5);
	MoveToEx(hdc, ROUND(Points[0].x), ROUND(Points[0].y), NULL);

	for (int i = 1; i < 4; i++)
	{
		Ellipse(hdc, ROUND(Points[i].x) - 5, ROUND(Points[i].y) - 5, ROUND(Points[i].x) + 5, ROUND(Points[i].y) + 5);
		LineTo(hdc, ROUND(Points[i].x), ROUND(Points[i].y));
	}


	SelectObject(hdc, hPenOld);
	SelectObject(hdc, hBrushOld);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

