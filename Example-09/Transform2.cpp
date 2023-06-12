#include "Transform2.h"
#include <math.h>
#define PI 3.141592653589793

Transform2::Transform2()
{
	
}

Transform2::~Transform2()
{
}

// ���ö�ά��������
void Transform2::SetMatrix(P2* p, int ptNumber)
{
	this->P = p;
	this->ptNumber = ptNumber;
}

// ��λ����
void Transform2::Identity()
{
	M[0][0] = 1.0; M[0][1] = 0.0; M[0][2] = 0.0;
	M[1][0] = 0.0; M[1][1] = 1.0; M[1][2] = 0.0;
	M[2][0] = 0.0; M[2][1] = 0.0; M[2][2] = 1.0;
}

// ƽ�Ʊ任����
void Transform2::Translate(double tx, double ty) 
{
	Identity();
	M[0][2] = tx;
	M[1][2] = ty;
	MultiplyMatrix();
}

// �����任����
void Transform2::Scale(double sx, double sy)
{
	Identity();
	M[0][0] = sx;
	M[1][1] = sy;
	MultiplyMatrix();
}

// ����������ı����任
void Transform2::Scale(double sx, double sy, P2 p)
{
	Translate(-p.x, -p.y);
	Scale(sx, sy);
	Translate(p.x, p.y);
}

// ��ת�任����
void Transform2::Rotate(double beta)
{
	Identity();
	M[0][0] = cos(beta * PI / 180); M[0][1] = -sin(beta * PI / 180);
	M[1][0] = sin(beta * PI / 180); M[1][1] =  cos(beta * PI / 180);
	MultiplyMatrix();
}

// ��ת�任����
void Transform2::Rotate(double beta, P2 p)
{
	Translate(-p.x, -p.y);
	Rotate(beta);
	Translate(p.x, p.y);
}

// ԭ�㷴��任
void Transform2::ReflectOrg(void)
{
	Identity();
	M[0][0] = -1;
	M[1][1] = -1;
	MultiplyMatrix();
}

// X�ᷴ��任����
void Transform2::ReflectX()
{
	Identity();
	M[0][0] = 1;
	M[1][1] = -1;
	MultiplyMatrix();
}

void Transform2::ReflectY()
{
	Identity();
	M[0][0] = -1;
	M[1][1] = 1;
	MultiplyMatrix();
}

// ���б任����
void Transform2::Shear(double b, double c)
{
	Identity();
	M[0][1] = b;
	M[1][0] = c;
	MultiplyMatrix();
}
// �������
void Transform2::MultiplyMatrix()
{
	P2* pTemp = new P2[ptNumber];
	for (int i = 0; i < ptNumber; i++)
	{
		pTemp[i] = P[i];

	}

	for (int i = 0; i < ptNumber; i++)
	{
		P[i].x = M[0][0] * pTemp[i].x + M[0][1] * pTemp[i].y + M[0][2] * pTemp[i].w;
		P[i].y = M[1][0] * pTemp[i].x + M[1][1] * pTemp[i].y + M[1][2] * pTemp[i].w;
		P[i].w = M[2][0] * pTemp[i].x + M[2][1] * pTemp[i].y + M[2][2] * pTemp[i].w;
	}

	delete[]pTemp;
}
