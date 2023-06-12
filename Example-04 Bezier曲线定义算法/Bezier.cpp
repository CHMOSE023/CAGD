#include "Bezier.h"
#include <math.h>
Bezier::Bezier() {}
Bezier::~Bezier() {}

void Bezier::ReadPoint(P2* points, int num)
{
	Points = points;
	Num = num;
};

void Bezier::Draw(HDC hdc) 
{
	MoveToEx(hdc, ROUND(Points[0].x), ROUND(Points[0].y), NULL);
	double tStep = 0.01;
	for (double t = 0; t < 1.0; t += tStep)
	{
		double x = 0.0, y = 0.0;
		for (int i = 0; i < Num + 1; i++)
		{
			x += Points[i].x * Cni(Num, i) * pow(t, i) * pow(1 - t, Num - i); //pow 幂函数
			y += Points[i].y * Cni(Num, i) * pow(t, i) * pow(1 - t, Num - i);
		}
		LineTo(hdc, ROUND(x), ROUND(y));
	}

}

void Bezier::DrawControlPolygon(HDC hdc)
{
	for (int i = 0; i < Num + 1; i++)
	{
		
		// 绘制圆
		Ellipse(hdc, ROUND(Points[i].x ) - 5, ROUND(Points[i].y ) - 5, ROUND(Points[i].x ) + 5, ROUND(Points[i].y ) + 5);

		// 绘制线
		if (0 == i)
		{
			MoveToEx(hdc, ROUND(Points[i].x), ROUND(Points[i].y), NULL);
		}
		else
		{
			LineTo(hdc, ROUND(Points[i].x), ROUND(Points[i].y));
		}
	}
}

double Bezier::Cni(int n,  int i)
{
	return double(Factorial(n)) / (Factorial(i) * Factorial(n - i));
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