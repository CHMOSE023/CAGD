#pragma once
#include <Windows.h>
#include "P2.h"
class Bezier
{
public:
	Bezier() {};
	~Bezier() {};

	// 读取点
	void ReadPoint(P2* p2Points, int n)
	{
		m_Count = n;
		for (size_t i = 0; i < n + 1; i++)
		{
			m_P2Points[i] = p2Points[i];
		}	
	};

	// 阶乘函数 
	int Factorial(int n)
	{
		int factorial;

		if (n == 0 || n == 1) 
		{
			factorial = 1;
		}
		else
		{
			factorial = n * Factorial(n - 1); // 递归 n - 1 
		}

		return factorial;
	}

	// 绘制 bezier
	void Draw(HDC hdc)
	{
	};

	// 绘制控制多边形
	void DrawControlPolygon(HDC hdc)
	{

	}
public:
	P2  m_P2Points[4];
	int m_Count; //曲线次数
};

