#include "Cube.h"

void Cube::ReadVertex() // 点表
{
	P[0].x = 0; P[0].y = 0; P[0].z = 0;
	P[1].x = 1; P[1].y = 0; P[1].z = 0;
	P[2].x = 1; P[2].y = 1; P[2].z = 0;
	P[3].x = 0; P[3].y = 1; P[3].z = 0;
	P[4].x = 0; P[4].y = 0; P[4].z = 1;
	P[5].x = 1; P[5].y = 0; P[5].z = 1;
	P[6].x = 1; P[6].y = 1; P[6].z = 1;
	P[7].x = 0; P[7].y = 1; P[7].z = 1;
}

void Cube::ReadFacet() // 面表
{
	F[0].Index[0] = 4; F[0].Index[1] = 5; F[0].Index[2] = 6; F[0].Index[3] = 7;	 //前
	F[1].Index[0] = 0; F[1].Index[1] = 3; F[1].Index[2] = 2; F[1].Index[3] = 1;	 //后
	F[2].Index[0] = 0; F[2].Index[1] = 4; F[2].Index[2] = 7; F[2].Index[3] = 3;	 //左
	F[3].Index[0] = 1; F[3].Index[1] = 2; F[3].Index[2] = 6; F[3].Index[3] = 5;	 //右
	F[4].Index[0] = 2; F[4].Index[1] = 3; F[4].Index[2] = 7; F[4].Index[3] = 6;	 //顶
	F[5].Index[0] = 0; F[5].Index[1] = 1; F[5].Index[2] = 5; F[5].Index[3] = 4;	 //底

}

P3* Cube::GetPoints() 
{
	return P;
}

void Cube::Draw(HDC hdc)
{
	P2 screenPoint;
	P2 temp;
	

	for (int nFace = 0; nFace < 6; nFace++) // 面
	{
		for (int nPoint = 0; nPoint < 4; nPoint++)
		{
			screenPoint = projection.PerspectiveProjection(P[F[nFace].Index[nPoint]]);

			if (0 == nPoint)
			{
				MoveToEx(hdc, ROUND(screenPoint.x), ROUND(screenPoint.y), NULL);
				temp = screenPoint;
			}
			else
			{
				LineTo(hdc, ROUND(screenPoint.x), ROUND(screenPoint.y));

			}
		}

		LineTo(hdc, ROUND(temp.x), ROUND(temp.y));// 闭合四边形

	}

}