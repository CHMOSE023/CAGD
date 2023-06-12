#include "Bezier.h"
#include <math.h>
Bezier::Bezier() {}
Bezier::~Bezier(){}

void Bezier::ReadPoint(P2* points, int num)
{	
	Points = points;
	Num = num;	
};

void Bezier::Draw(HDC hdc)
{
	// ��ʼ����������
	PPoints = new P2 * [Num + 1];
	for (int i = 0; i < Num + 1; i++)
	{
		PPoints[i] = new P2[Num + 1];
	}


	MoveToEx(hdc, ROUND(Points[0].x), ROUND(Points[0].y), NULL);
	double tStep = 0.03; // ����
	for (double t = 0.0; t <= 1.0; t += tStep)
	{
		DeCasteljau(t);
		LineTo(hdc, ROUND(PPoints[0][Num].x), ROUND(PPoints[0][Num].y));
	}


	// ɾ����������
	for (int i = 0; i < Num + 1; i++)
	{
		delete[]PPoints[i];
		PPoints[i] = NULL;
	}
	delete[]PPoints;
	PPoints = NULL;
}

void Bezier::DrawControlPolygon(HDC hdc)
{
	for (int i = 0; i < Num + 1; i++)
	{

		// ����Բ
		Ellipse(hdc, ROUND(Points[i].x) - 5, ROUND(Points[i].y) - 5, ROUND(Points[i].x) + 5, ROUND(Points[i].y) + 5);

		// ������
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

void Bezier::DeCasteljau(double t)
{
	for (int k = 0; k <= Num; k++)
	{
		PPoints[k][0] = Points[k];    // ���Ƶ�һά���鸳ֵ����ά		
	}

	for (int r = 1; r <= Num; r++)  // DeCasteljag ���ƹ�ʽ��ʹ�ö�ά����
	{
		for (int i = 0; i <= (Num - r); i++)
		{
			PPoints[i][r] = (1 - t) * PPoints[i][r - 1] + t * PPoints[i + 1][r - 1]; // ���ƹ�ʽ
		}
	}
}
