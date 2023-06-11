#pragma once
#include "math.h"
#define ROUND(d) int(d+0.5)
class P2D
{
public:
	P2D(void) { };
	P2D(double x, double y) { X = x; Y = y; };
	virtual ~P2D(void) {};

	friend P2D operator +  (const P2D& p0, const P2D& p1) 
	{
		P2D result;
		result.X = p0.X + p1.X;
		result.Y = p0.Y + p1.Y;
		return result;
	};

	friend P2D operator -  (const P2D& p0, const P2D& p1) 
	{
		P2D result;
		result.X = p0.X - p1.X;
		result.Y = p0.Y - p1.Y;
		return result;
	};

	friend P2D operator -  (double scalar, const P2D& p)
	{
		P2D result;
		result.X = scalar - p.X;
		result.Y = scalar - p.Y;
		return result;
	};

	friend P2D operator -  (const P2D& p, double scalar) 
	{
		P2D result;
		result.X = p.X - scalar;
		result.Y = p.Y - scalar;
		return result;
	};

	friend P2D operator *  (const P2D& p, double scalar)
	{
		return P2D(p.X * scalar, p.Y * scalar);
	}	;
	friend P2D operator *  (double scalar, const P2D& p)
	{
		return P2D(p.X * scalar, p.Y * scalar);
	};

	friend P2D operator /  (const P2D& p0, P2D& p1) 
	{
		if (fabs(p1.X) < 1e-6)
			p1.X = 1.0;
		if (fabs(p1.Y) < 1e-6)
			p1.Y = 1.0;

		P2D result;
		result.X = p0.X / p0.X;
		result.Y = p0.Y / p0.Y;
		return result;

	};

	friend P2D operator /  (const P2D& p, double scalar) 
	{
		if (fabs(scalar) < 1e-6) // fabs 取绝对值  1e-6  0.000001
		{
			scalar = 1.0;
		}

		P2D result;
		result.X = p.X / scalar;
		result.Y = p.Y / scalar;
		return result;
	};

	friend P2D operator += (P2D& p0, const P2D& p1)
	{
		p0.X += p1.X;
		p0.Y += p1.Y;
		return p0;
	}
	;
	friend P2D operator -= (P2D& p0, const P2D& p1)
	{
		p0.X -= p1.X;
		p0.Y -= p1.Y;
		return p0;
	};

	friend P2D operator *= (P2D& p, double scalar)
	{
		p.X *= scalar;
		p.Y *= scalar;
		return p;
	};

	friend P2D operator /= (P2D& p, double scalar)
	{
		if (fabs(scalar) < 1e-6) // fabs 取绝对值  1e-6  0.000001
		{
			scalar = 1.0;
		}
		p.X /= scalar;
		p.Y /= scalar;
		p.Y /= scalar;
		return p;
	};

public:
	double X = 0;
	double Y = 0;
};