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
	void DeCasteljau(double t);
	
public:	
	P2*  Points;	   // 控制点数组
	P2** PPoints;	   // 递推数组 
	int  Num;		   // 曲线次数
};

