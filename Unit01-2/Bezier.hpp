#pragma once
#include <Windows.h>
#include "P2.h"
class Bezier
{
public:
	Bezier() {};
	~Bezier() {};

	// ��ȡ��
	void ReadPoint(P2* p2Points, int n)
	{
		m_Count = n;
		for (size_t i = 0; i < n + 1; i++)
		{
			m_P2Points[i] = p2Points[i];
		}	
	};

	// �׳˺��� 
	int Factorial(int n)
	{
		int factorial;

		if (n == 0 || n == 1) 
		{
			factorial = 1;
		}
		else
		{
			factorial = n * Factorial(n - 1); // �ݹ� n - 1 
		}

		return factorial;
	}

	// ���� bezier
	void Draw(HDC hdc)
	{
	};

	// ���ƿ��ƶ����
	void DrawControlPolygon(HDC hdc)
	{

	}
public:
	P2  m_P2Points[4];
	int m_Count; //���ߴ���
};

