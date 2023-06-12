// ש�鵥Ԫ
#pragma once
#include "P2.h"
#include "BaseWindow.hpp"

class Brick
{
public:
	Brick(void);
	~Brick(void);
	void ReadPoint(void);
	void Draw(HDC hdc);

public:
	P2 P[4];

};

