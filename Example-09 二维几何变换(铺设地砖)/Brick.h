// ש�鵥Ԫ
#pragma once
#include "P2.h"
#include "BaseWindow.h"

class Brick
{
public:
	Brick(void);
	~Brick(void);
	void ReadPoint(void);
	void Draw(HDC hdc);

public:
	P2  Points[4];
};

