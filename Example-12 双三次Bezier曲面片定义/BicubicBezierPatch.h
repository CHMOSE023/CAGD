#pragma once
#include <Windows.h>
#include"P2.h"
#include"P3.h"
#include "Projection.h"
/// <summary>
/// 双三次Bezier曲面片
/// </summary>
class BicubicBezierPatch
{
public:
	BicubicBezierPatch();
	~BicubicBezierPatch();

	// 读取控制点
	void ReadControlPoint(P3 P[4][4]);

	// 绘制曲面
	void DrawCurvedPatch(HDC hdc);

	// 绘制控制点
	void DrawControlGrid(HDC hdc);

private:
	// 左乘顶点矩阵
	void LeftMultiplyMatrix(double M[4][4], P3 P[4][4]);
	// 右乘顶点矩阵
	void RightMultiplyMatrix(P3 P[4][4], double M[4][4]);
	// 转置矩阵
	void TransposeMatrix(double M[4][4]);
	// 斜二测投影
	P2 ObliqueProjection(P3 Point3);
public:
	//三维控制点
	P3 P[4][4]; 
	Projection projection;
};

