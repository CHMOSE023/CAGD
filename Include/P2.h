#pragma once
#include <math.h>
#define ROUND(d) int(d+0.5)
class P2
{
public:
	P2() { x = 0; y = 0; w = 0; };
	P2(double x, double y)
	{
		this->x = x;
		this->y = y;
		this->w = 1;
	};
	virtual ~P2() {};
	friend P2 operator +  (const P2& p0, const P2& p1)
	{
		P2 result;
		result.x = p0.x + p1.x;
		result.y = p0.y + p1.y;
		return result;
	};

	friend P2 operator -  (const P2& p0, const P2& p1)
	{
		P2 result;
		result.x = p0.x - p1.x;
		result.y = p0.y - p1.y;
		return result;
	};

	friend P2 operator -  (double scalar, const P2& p)
	{
		P2 result;
		result.x = scalar - p.x;
		result.y = scalar - p.y;
		return result;
	};

	friend P2 operator -  (const P2& p, double scalar)
	{
		P2 result;
		result.x = p.x - scalar;
		result.y = p.y - scalar;
		return result;
	};

	friend P2 operator *  (const P2& p, double scalar)
	{
		return P2(p.x * scalar, p.y * scalar);
	};
	friend P2 operator *  (double scalar, const P2& p)
	{
		return P2(p.x * scalar, p.y * scalar);
	};

	friend P2 operator /  (const P2& p0, P2& p1)
	{
		if (fabs(p1.x) < 1e-6)
			p1.x = 1.0;
		if (fabs(p1.y) < 1e-6)
			p1.y = 1.0;

		P2 result;
		result.x = p0.x / p0.x;
		result.y = p0.y / p0.y;
		return result;

	};

	friend P2 operator /  (const P2& p, double scalar)
	{
		if (fabs(scalar) < 1e-6) // fabs 取绝对值  1e-6  0.000001
		{
			scalar = 1.0;
		}

		P2 result;
		result.x = p.x / scalar;
		result.y = p.y / scalar;
		return result;
	};

	friend P2 operator += (P2& p0, const P2& p1)
	{
		p0.x += p1.x;
		p0.y += p1.y;
		return p0;
	}
	;
	friend P2 operator -= (P2& p0, const P2& p1)
	{
		p0.x -= p1.x;
		p0.y -= p1.y;
		return p0;
	};

	friend P2 operator *= (P2& p, double scalar)
	{
		p.x *= scalar;
		p.y *= scalar;
		return p;
	};

	friend P2 operator /= (P2& p, double scalar)
	{
		if (fabs(scalar) < 1e-6) // fabs 取绝对值  1e-6  0.000001
		{
			scalar = 1.0;
		}
		p.x /= scalar;
		p.y /= scalar;
		p.y /= scalar;
		return p;
	};

public:
	double x; 
	double y; 
	double w; 
};


