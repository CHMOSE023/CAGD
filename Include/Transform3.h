#pragma once
#include "P3.h"
#define PI 3.1415926
#include <math.h>
class Transform3
{
public:
	Transform3() {};
	~Transform3() {};
	void SetMatrix(P3* points, int number) {
		Points = points;
		Number = number;
	}
	void Identity() //µ¥Î»¾ØÕó
	{
		T[0][0] = 1.0; T[0][1] = 0.0; T[0][2] = 0.0; T[0][3] = 0.0;
		T[1][0] = 0.0; T[1][1] = 1.0; T[1][2] = 0.0; T[1][3] = 0.0;
		T[2][0] = 0.0; T[2][1] = 0.0; T[2][2] = 1.0; T[2][3] = 0.0;
		T[3][0] = 0.0; T[3][1] = 0.0; T[3][2] = 0.0; T[3][3] = 1.0;
	}
	void Translate(double tx, double ty, double tz) //Æ½ÒÆ±ä»»¾ØÕó
	{
		Identity();
		T[0][3] = tx;
		T[1][3] = ty;
		T[2][3] = tz;
		MultiplyMatrix();
	}
	void RotateX(double beta) //ÈÆXÖáĞı×ª±ä»»¾ØÕó
	{
		Identity();
		double rad = beta * PI / 180;
		T[1][1] = cos(rad); T[1][2] = -sin(rad);
		T[2][1] = sin(rad); T[2][2] = cos(rad);
		MultiplyMatrix();
	}
	void RotateY(double beta) //ÈÆYÖáĞı×ª±ä»»¾ØÕó
	{
		Identity();
		double rad = beta * PI / 180;
		T[0][0] = cos(rad); T[0][2] = sin(rad);
		T[2][0] = -sin(rad); T[2][2] = cos(rad);
		MultiplyMatrix();
	}
	void RotateZ(double beta) //Ğı×ª±ä»»¾ØÕó
	{
		Identity();
		double rad = beta * PI / 180;
		T[0][0] = cos(rad); T[0][1] = -sin(rad);
		T[1][0] = sin(rad); T[1][1] = cos(rad);
		MultiplyMatrix();
	}
	void MultiplyMatrix() //¾ØÕóÏà³Ë
	{
		P3* pTemp = new P3[Number];
		for (int i = 0; i < Number; i++)
			pTemp[i] = Points[i];

		for (int j = 0; j < Number; j++)
		{
			Points[j].x = T[0][0] * pTemp[j].x + T[0][1] * pTemp[j].y + T[0][2] * pTemp[j].z + T[0][3] * pTemp[j].w;
			Points[j].y = T[1][0] * pTemp[j].x + T[1][1] * pTemp[j].y + T[1][2] * pTemp[j].z + T[1][3] * pTemp[j].w;
			Points[j].z = T[2][0] * pTemp[j].x + T[2][1] * pTemp[j].y + T[2][2] * pTemp[j].z + T[2][3] * pTemp[j].w;
			Points[j].w = T[3][0] * pTemp[j].x + T[3][1] * pTemp[j].y + T[3][2] * pTemp[j].z + T[3][3] * pTemp[j].w;
		}
		delete[]pTemp;
	}
public:
	double T[4][4] = {0};
	P3*    Points=nullptr;
	int    Number=0;
};