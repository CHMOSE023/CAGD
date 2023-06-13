#include "BicubicBezierPatch.h"

BicubicBezierPatch::BicubicBezierPatch()
{
}

BicubicBezierPatch::~BicubicBezierPatch()
{
}

void BicubicBezierPatch::ReadControlPoint(P3 P[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->P[i][j] = P[i][j];
		}
	}
}

void BicubicBezierPatch::DrawCurvedPatch(HDC hdc)
{
	double M[4][4] = {}; // 系数矩阵Mbe
	M[0][0] = -1; M[0][1] =  3; M[0][2] = -3; M[0][3] = 1;
	M[1][0] =  3; M[1][1] = -6; M[1][2] =  3; M[1][3] = 0;
	M[2][0] = -3; M[2][1] =  3; M[2][2] =  0; M[2][3] = 0;
	M[3][0] =  1; M[3][1] =  0; M[3][2] =  0; M[3][3] = 0;

	// 曲线计算用控制点数组
	P3 p3[4][4];    
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			p3[i][j] = P[i][j];
		}
	}
	// 数字矩阵左乘三维点矩阵
	LeftMultiplyMatrix(M, p3);

	// 计算转置矩阵
	TransposeMatrix(M);

	// 数字矩阵右乘三维点矩阵
	RightMultiplyMatrix(p3, M);

	double tStep = 0.1;
	
	//u,v参数的幂
	double u0, u1, u2, u3, v0, v1, v2, v3;

	for (double u = 0; u <= 1; u+= tStep)
	{
		for (double v = 0; v <=1; v += tStep)
		{
			u3 = u * u * u;
			u2 = u * u;
			u1 = u;
			u0 = 1;

			v3 = v * v * v;
			v2 = v * v;
			v1 = v;
			v0 = 1;

			P3 pt = (u3 * p3[0][0] + u2 * p3[1][0] + u1 * p3[2][0] + u0 * p3[3][0]) * v3
				  + (u3 * p3[0][1] + u2 * p3[1][1] + u1 * p3[2][1] + u0 * p3[3][1]) * v2
				  + (u3 * p3[0][2] + u2 * p3[1][2] + u1 * p3[2][2] + u0 * p3[3][2]) * v1
				  + (u3 * p3[0][3] + u2 * p3[1][3] + u1 * p3[2][3] + u0 * p3[3][3]) * v0;

			// 倾斜二测投影
			P2 point2 = projection.ObliqueProjection(pt);

			if (0 == v) 
			{
				MoveToEx(hdc, ROUND(point2.x), ROUND(point2.y), NULL);
			}
			else
			{
				LineTo(hdc, ROUND(point2.x), ROUND(point2.y));
			}
		}

		for (double v = 0; v <= 1; v+= tStep)
		{
			for (double u = 0; u <= 1; u+= tStep)
			{
				u3 = u * u * u;
				u2 = u * u;
				u1 = u;
				u0 = 1;

				v3 = v * v * v;
				v2 = v * v;
				v1 = v;
				v0 = 1;

				P3 pt = (u3 * p3[0][0] + u2 * p3[1][0] + u1 * p3[2][0] + u0 * p3[3][0]) * v3
					  + (u3 * p3[0][1] + u2 * p3[1][1] + u1 * p3[2][1] + u0 * p3[3][1]) * v2
					  + (u3 * p3[0][2] + u2 * p3[1][2] + u1 * p3[2][2] + u0 * p3[3][2]) * v1
					  + (u3 * p3[0][3] + u2 * p3[1][3] + u1 * p3[2][3] + u0 * p3[3][3]) * v0;

				// 倾斜二测投影
				P2 point2 =  projection.ObliqueProjection(pt);

				if (0 == u)
				{
					MoveToEx(hdc, ROUND(point2.x), ROUND(point2.y), NULL);
				}
				else
				{
					LineTo(hdc, ROUND(point2.x), ROUND(point2.y));
				}
			}
		}
	}

}
// 绘制控制网格
void BicubicBezierPatch::DrawControlGrid(HDC hdc)
{
	P2 p2[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			p2[i][j] = projection.ObliqueProjection(P[i][j]);
		}
	}

	HPEN hPen, oldPen;
	hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	oldPen = (HPEN)SelectObject(hdc, hPen);

	for (int i = 0; i < 4; i++)
	{
		MoveToEx(hdc, ROUND(p2[i][0].x), ROUND(p2[i][0].y), NULL);
		for (int j = 0; j < 4; j++)
		{
			LineTo(hdc, ROUND(p2[i][j].x), ROUND(p2[i][j].y));
		}
	}

	for (int j = 0; j < 4; j++)
	{
		MoveToEx(hdc, ROUND(p2[0][j].x), ROUND(p2[0][j].y), NULL);
		for (int i = 0; i < 4; i++)
		{
			LineTo(hdc, ROUND(p2[i][j].x), ROUND(p2[i][j].y));
		}
	}

	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
}

// 左乘矩阵
void BicubicBezierPatch::LeftMultiplyMatrix(double M[4][4], P3 P[4][4])
{
	P3 T[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			T[i][j] = M[i][0] * P[0][j] + M[i][1] * P[1][j] + M[i][2] * P[2][j] + M[i][3] * P[3][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			P[i][j] = T[i][j];
		}
	}
}
// 右乘矩阵
void BicubicBezierPatch::RightMultiplyMatrix(P3 P[4][4], double M[4][4])
{
	P3 T[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			T[i][j] = P[i][0] * M[0][j] + P[i][1] * M[1][j] + P[i][2] * M[2][j] + P[i][3] * M[3][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			P[i][j] = T[i][j];
		}
	}
}

// 转置矩阵
void BicubicBezierPatch::TransposeMatrix(double M[4][4])
{
	double T[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			T[j][i] = M[i][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			M[i][j]=T[i][j];
		}
	}
}

// 斜二测投影
P2 BicubicBezierPatch::ObliqueProjection(P3 Point3)
{
	P2 Point2;

	Point2.x = Point3.x - Point3.z * sqrt(2.0) / 2.0;
	Point2.y = Point3.y - Point3.z * sqrt(2.0) / 2.0;

	return Point2;
}


