#pragma once
#include "P3.h"
#include "Projection.h"
#include "Facet.h"
#include <Windows.h>
class Cube
{
public:
	Cube() {};
	virtual ~Cube() {};
	void ReadVertex();
	void ReadFacet();
	P3*  GetPoints();// ��ö���������
	void Draw(HDC hdc);

private:
	P3         P[8];
	Facet      F[6];
	Projection projection;
};

