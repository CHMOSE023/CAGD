#pragma once
#include "P2.h"
#include "BaseWindow.h"
class Bezier
{
public:
	Bezier();
	~Bezier();
	void ReadPoint(P2* points, int num);
	void Draw(HDC hdc);
	void DrawControlPolygon(HDC hdc);
private:
	double Cni(int n,  int i);
	int Factorial(int n);
public:
	P2* Points;
	int Num;
};

