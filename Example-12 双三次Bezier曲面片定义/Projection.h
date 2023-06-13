#pragma once
#include "P3.h"
/// <summary>
/// 投影变换
/// </summary>
class Projection
{
public:
	Projection();
	virtual ~Projection();
	void  InitialPatameter();
	void SetEye(double R, double	Phi, double Theta); //设置视点
	P3 GetEye();   //获取视点
	P2 ObliqueProjection(P3 worldPoint);     // 倾投影
	P2 OrthogonalProjection(P3 worldPoint);  // 正交投影 
	P2 PerspectiveProjection(P3 worldPoint); // 透视投影

private:
	P3 EyePoint; // 视点
	double R;    // 视径
	double d;    // 视距
	double Phi;  // 角度
	double Theta;//
	double k[8]; // 透视投影常数

};

