#pragma once
#include <Windows.h>
#include "P2.h"
#include "CubivBezierCurve.h"
class Ellipse
{
public :
	Ellipse();
	~Ellipse();
	void ReadPoint();
	void Draw(HDC hdc);
public:
	P2 P[12];
private:
	CubivBezierCurve bezier[4];
};

