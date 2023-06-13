#pragma once
#include "P2.h"
#include <math.h>
#define PI 3.141592653589793
class Transform2
{
public:
	Transform2() {};
	virtual ~Transform2() {};

	// ���ö�ά��������
	void SetMatrix(P2* points, int number)	    
	{
		this->Points = points;
		this->Number = number;
	}

	// ��λ����
	void Identity()						    
	{
		M[0][0] = 1.0; M[0][1] = 0.0; M[0][2] = 0.0;
		M[1][0] = 0.0; M[1][1] = 1.0; M[1][2] = 0.0;
		M[2][0] = 0.0; M[2][1] = 0.0; M[2][2] = 1.0;
	}

	// ƽ�Ʊ任����
	void Translate(double tx, double ty)	
	{
		Identity();
		M[0][2] = tx;
		M[1][2] = ty;
		MultiplyMatrix();
	}

	// �����任����
	void Scale(double sx, double sy)		
	{
		Identity();
		M[0][0] = sx;
		M[1][1] = sy;
		MultiplyMatrix();
	}

	// ����������ı����任
	void Scale(double sx, double sy, P2 p)   
	{
		Translate(-p.x, -p.y);
		Scale(sx, sy);
		Translate(p.x, p.y);
	}

	// ��ת�任����
	void Rotate(double beta)				
	{
		Identity();
		M[0][0] = cos(beta * PI / 180); M[0][1] = -sin(beta * PI / 180);
		M[1][0] = sin(beta * PI / 180); M[1][1] = cos(beta * PI / 180);
		MultiplyMatrix();
	}

	// �����һ����ת�任
	void Rotate(double beta, P2 p)			
	{
		Translate(-p.x, -p.y);
		Rotate(beta);
		Translate(p.x, p.y);
	}

	// ԭ�㷴��任
	void ReflectOrg(void)					
	{
		Identity();
		M[0][0] = -1;
		M[1][1] = -1;
		MultiplyMatrix();
	}

	// X�ᷴ��任����
	void ReflectX()						
	{
		Identity();
		M[0][0] = 1;
		M[1][1] = -1;
		MultiplyMatrix();
	}

	// Y�ᷴ��任����
	void ReflectY()						
	{
		Identity();
		M[0][0] = -1;
		M[1][1] = 1;
		MultiplyMatrix();
	}

	// ���б任����
	void Shear(double b, double c)			
	{
		Identity();
		M[0][1] = b;
		M[1][0] = c;
		MultiplyMatrix();
	}

	// �������
	void MultiplyMatrix()					
	{
		P2* pTemp = new P2[Number];
		for (int i = 0; i < Number; i++)
		{
			pTemp[i] = Points[i];

		}

		for (int i = 0; i < Number; i++)
		{
			Points[i].x = M[0][0] * pTemp[i].x + M[0][1] * pTemp[i].y + M[0][2] * pTemp[i].w;
			Points[i].y = M[1][0] * pTemp[i].x + M[1][1] * pTemp[i].y + M[1][2] * pTemp[i].w;
			Points[i].w = M[2][0] * pTemp[i].x + M[2][1] * pTemp[i].y + M[2][2] * pTemp[i].w;
		}

		delete[]pTemp;
	}
private:
	double  M[3][3] = {0};   // �任����
	P2*     Points;	   // ��������
	int     Number;    // �������

};
