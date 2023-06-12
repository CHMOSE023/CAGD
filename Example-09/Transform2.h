// 二维变换
#pragma once
#include "P2.h"
class Transform2
{
public:
	Transform2();
	virtual ~Transform2();
	void SetMatrix(P2* p, int ptNumber);	// 设置二维顶点数组
	void Identity();						// 单位矩阵
	void Translate(double tx, double ty);	// 平移变换矩阵
	void Scale(double sx, double sy);		// 比例变换矩阵
	void Scale(double sx,double sy,P2 p);   // 相对与任意点的比例变换
	void Rotate(double beta);				// 旋转变换矩阵
	void Rotate(double beta, P2 p);			// 相对任一点旋转变换
	void ReflectOrg(void);					// 原点反射变换
	void ReflectX();						// X轴反射变换矩阵
	void ReflectY();						// Y轴反射变换矩阵
	void Shear(double b, double c);			// 错切变换矩阵
	void MultiplyMatrix();					// 矩阵相乘
private:
	double  M[3][3];   // 变换矩阵
	P2*     P;		   // 顶点数组
	int     ptNumber;  // 顶点个数

};
