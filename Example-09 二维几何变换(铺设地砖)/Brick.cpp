#include "Brick.h"

Brick::Brick() {};
Brick::~Brick() {};

void Brick::ReadPoint()
{
	Points[0] = P2(-0.5, -0.5);
	Points[1] = P2(0.5, -0.5);
	Points[2] = P2(0.5, 0.5);
	Points[3] = P2(-0.5, 0.5);
}

void Brick::Draw(HDC hdc)
{
	MoveToEx(hdc, ROUND(Points[0].x), ROUND(Points[0].y), NULL);
	LineTo(hdc,   ROUND(Points[1].x), ROUND(Points[1].y));
	LineTo(hdc,   ROUND(Points[2].x), ROUND(Points[2].y));
	LineTo(hdc,   ROUND(Points[3].x), ROUND(Points[3].y));
	LineTo(hdc,   ROUND(Points[0].x), ROUND(Points[0].y));

	MoveToEx(hdc, ROUND((Points[0].x + Points[3].x) / 2), ROUND((Points[0].y + Points[3].y) / 2), NULL);
	LineTo(hdc,   ROUND((Points[1].x + Points[2].x) / 2), ROUND((Points[1].y + Points[2].y) / 2));
}