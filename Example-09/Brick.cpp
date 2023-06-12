#include "Brick.h"

Brick::Brick() {};
Brick::~Brick() {};

void Brick::ReadPoint()
{
	P[0] = P2(-0.5, -0.5);
	P[1] = P2( 0.5, -0.5);
	P[2] = P2( 0.5,  0.5);
	P[3] = P2(-0.5,  0.5);
}

void Brick::Draw(HDC hdc)
{
	MoveToEx(hdc, ROUND(P[0].x), ROUND(P[0].y), NULL);
	LineTo(hdc, ROUND(P[1].x), ROUND(P[1].y));
	LineTo(hdc, ROUND(P[2].x), ROUND(P[2].y));
	LineTo(hdc, ROUND(P[3].x), ROUND(P[3].y));
	LineTo(hdc, ROUND(P[0].x), ROUND(P[0].y));

	MoveToEx(hdc, ROUND((P[0].x+ P[3].x)/2), ROUND((P[0].y + P[3].y) / 2), NULL);
	LineTo(hdc, ROUND((P[1].x+ P[2].x)/2), ROUND((P[1].y + P[2].y) / 2));
}