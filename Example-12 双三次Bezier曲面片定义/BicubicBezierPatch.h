#pragma once
#include <Windows.h>
#include"P2.h"
#include"P3.h"
#include "Projection.h"
/// <summary>
/// ˫����Bezier����Ƭ
/// </summary>
class BicubicBezierPatch
{
public:
	BicubicBezierPatch();
	~BicubicBezierPatch();

	// ��ȡ���Ƶ�
	void ReadControlPoint(P3 P[4][4]);

	// ��������
	void DrawCurvedPatch(HDC hdc);

	// ���ƿ��Ƶ�
	void DrawControlGrid(HDC hdc);

private:
	// ��˶������
	void LeftMultiplyMatrix(double M[4][4], P3 P[4][4]);
	// �ҳ˶������
	void RightMultiplyMatrix(P3 P[4][4], double M[4][4]);
	// ת�þ���
	void TransposeMatrix(double M[4][4]);
	// б����ͶӰ
	P2 ObliqueProjection(P3 Point3);
public:
	//��ά���Ƶ�
	P3 P[4][4]; 
	Projection projection;
};

