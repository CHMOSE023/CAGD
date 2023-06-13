#pragma once
#include <math.h>
#include "p2.h"
class P3 : public P2
{
public:
	P3(void) {z = 0.0;w=1.0;};
	~P3(void) {};
	P3(double x, double y, double z) :P2(x, y) { this->z = z; };

	//运算符重载
	friend P3 operator +(const P3& p0, const P3& p1) 	// 和
	{
		P3 result;
		result.x = p0.x + p1.x;
		result.y = p0.y + p1.y;
		result.z = p0.z + p1.z;
		return result;
	} 		
	friend P3 operator -(const P3& p0, const P3& p1) // 差
	{
		P3 result;
		result.x = p0.x - p1.x;
		result.y = p0.y - p1.y;
		result.z = p0.z - p1.z;
		return result;
	}
	friend P3 operator *(const P3& p, double scalar) 	// 点和常量的积
	{
		return P3(p.x * scalar, p.y * scalar, p.z * scalar);
	}	
	friend P3 operator *(double scalar, const P3& p)  // 点和常量的积
	{
		return P3(p.x * scalar, p.y * scalar, p.z * scalar);
	}	
	friend P3 operator /(const P3& p, double scalar)  // 数除
	{
		if (fabs(scalar) < 1e-6)
			scalar = 1.0;
		P3 result;
		result.x = p.x / scalar;
		result.y = p.y / scalar;
		result.z = p.z / scalar;
		return result;
	}
	friend P3 operator+=(P3& p0, const P3& p1)
	{
		p0.x = p0.x + p1.x;
		p0.y = p0.y + p1.y;
		p0.z = p0.z + p1.z;
		return p0;
	}
	friend P3 operator-=(P3& p0, const P3& p1) 
	{
		p0.x = p0.x - p1.x;
		p0.y = p0.y - p1.y;
		p0.z = p0.z - p1.z;
		return p0;
	}
	friend P3 operator*=(P3& p0, double scalar)
	{
		p0.x = p0.x * scalar;
		p0.y = p0.y * scalar;
		p0.z = p0.z * scalar;
		return p0;
	}
	friend P3 operator/=(P3& p0, double scalar)
	{
		if (fabs(scalar) < 1e-6)
			scalar = 1.0;
		p0.x = p0.x / scalar;
		p0.y = p0.y / scalar;
		p0.z = p0.z / scalar;
		return p0;
	}

public:
	double z;
};

