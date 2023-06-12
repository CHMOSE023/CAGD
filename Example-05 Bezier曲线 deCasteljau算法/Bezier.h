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
	P2*  Points;	   // ���Ƶ�����
	P2** PPoints;	   // �������� 
	int  Num;		   // ���ߴ���
};

