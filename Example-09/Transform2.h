// ��ά�任
#pragma once
#include "P2.h"
class Transform2
{
public:
	Transform2();
	virtual ~Transform2();
	void SetMatrix(P2* p, int ptNumber);	// ���ö�ά��������
	void Identity();						// ��λ����
	void Translate(double tx, double ty);	// ƽ�Ʊ任����
	void Scale(double sx, double sy);		// �����任����
	void Scale(double sx,double sy,P2 p);   // ����������ı����任
	void Rotate(double beta);				// ��ת�任����
	void Rotate(double beta, P2 p);			// �����һ����ת�任
	void ReflectOrg(void);					// ԭ�㷴��任
	void ReflectX();						// X�ᷴ��任����
	void ReflectY();						// Y�ᷴ��任����
	void Shear(double b, double c);			// ���б任����
	void MultiplyMatrix();					// �������
private:
	double  M[3][3];   // �任����
	P2*     P;		   // ��������
	int     ptNumber;  // �������

};
