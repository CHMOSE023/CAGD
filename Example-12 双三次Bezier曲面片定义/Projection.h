#pragma once
#include "P3.h"
/// <summary>
/// ͶӰ�任
/// </summary>
class Projection
{
public:
	Projection();
	virtual ~Projection();
	void  InitialPatameter();
	void SetEye(double R, double	Phi, double Theta); //�����ӵ�
	P3 GetEye();   //��ȡ�ӵ�
	P2 ObliqueProjection(P3 worldPoint);     // ��ͶӰ
	P2 OrthogonalProjection(P3 worldPoint);  // ����ͶӰ 
	P2 PerspectiveProjection(P3 worldPoint); // ͸��ͶӰ

private:
	P3 EyePoint; // �ӵ�
	double R;    // �Ӿ�
	double d;    // �Ӿ�
	double Phi;  // �Ƕ�
	double Theta;//
	double k[8]; // ͸��ͶӰ����

};

