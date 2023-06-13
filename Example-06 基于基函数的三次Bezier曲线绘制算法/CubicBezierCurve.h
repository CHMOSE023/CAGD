#pragma once
#include <Windows.h>
#include"P2.h"
class CubicBezierCurve
{
public:
	CubicBezierCurve();
	virtual ~CubicBezierCurve();

	void ReadPoint(P2* points);
	void Draw(HDC hdc);
	void DrawControlPolygon(HDC hdc);

public:
	P2* Points;
};

