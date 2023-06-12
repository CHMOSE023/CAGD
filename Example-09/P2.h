//二维点
#pragma once
#define ROUND(d) int(d+0.5)
class P2
{
public:
	P2();
	P2(double x, double y);
	virtual ~P2();

public:
	double x; // x
	double y; // y
	double w; // 齐次坐标

};

