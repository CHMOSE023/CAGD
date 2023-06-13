#include "Projection.h"

#define PI 3.1415926
Projection::Projection()
{
    EyePoint = {};
    R = 1000.0;
    d = 800.0;
    Phi = 90.0;
    Theta = 0.0;
    InitialPatameter();

}

Projection::~Projection()
{
}

void Projection::InitialPatameter()
{
    k[0] = sin(PI * Theta / 180);
    k[1] = sin(PI * Phi / 180);
    k[2] = cos(PI * Theta / 180);
    k[3] = cos(PI * Phi / 180);
    k[4] = k[1] * k[2];
    k[5] = k[0] * k[1];
    k[6] = k[2] * k[3];
    k[7] = k[0] * k[3];

    EyePoint = P3(R*k[5],R*k[3],R*k[4]); // �ӵ�λ��
}

void Projection::SetEye(double R, double	Phi, double Theta)
{
    this->R = R;
    this->Phi = Phi;
    this->Theta = Theta;

    InitialPatameter();
}

P3 Projection::GetEye()
{
    return EyePoint;
}

P2 Projection::ObliqueProjection(P3 worldPoint)
{
    return P2();
}

P2 Projection::OrthogonalProjection(P3 worldPoint)
{
    return P2();
}

P2 Projection::PerspectiveProjection(P3 worldPoint) // ͶӰ�㷨
{
    P3 viewPoint; // �۲�����ϵ 

    // 1.��������תΪ�۲�����
    viewPoint.x =  k[2] * worldPoint.x - k[0] * worldPoint.z;
    viewPoint.y = -k[7] * worldPoint.x + k[1] * worldPoint.y - k[6] * worldPoint.z;
    viewPoint.z = -k[5] * worldPoint.x - k[3] * worldPoint.y - k[4] * worldPoint.z + R;
    viewPoint.w = worldPoint.w;

    P2 screenPoint; //��Ļ����ϵ ��ά��

    // 2.�۲�����תΪ��Ļ����
    screenPoint.x = d * viewPoint.x / viewPoint.z;
    screenPoint.y = d * viewPoint.y / viewPoint.z;
    screenPoint.w = viewPoint.w;

    return screenPoint;
}
