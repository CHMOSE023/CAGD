#pragma once
#include"CubicBezierCurve.h"
namespace CAGD
{
	class Ellipse
	{
	public:
		Ellipse(void);
		~Ellipse(void);
		void ReadPoint(void);
		void Draw(HDC hdc);

	public:
		P2  Points[12];

	private:
		CubicBezierCurve Bezier[4];
	};

};