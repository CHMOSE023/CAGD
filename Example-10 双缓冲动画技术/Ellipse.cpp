#include "Ellipse.h"

CAGD::Ellipse::Ellipse() { }
CAGD::Ellipse::~Ellipse() { }

void CAGD::Ellipse::ReadPoint()
{
	  
	double m = 0.5523;
	Points[0].x = 1;  Points[0].y = 0;
	Points[1].x = 1;  Points[1].y = m;
	Points[2].x = m;  Points[2].y = 1;
	Points[3].x = 0;  Points[3].y = 1;
	Points[4].x = -m; Points[4].y = 1;
	Points[5].x = -1; Points[5].y = m;
	Points[6].x = -1; Points[6].y = 0;
	Points[7].x = -1; Points[7].y = -m;
	Points[8].x = -m; Points[8].y = -1;
	Points[9].x = 0;  Points[9].y = -1;
	Points[10].x = m; Points[10].y = -1;
	Points[11].x = 1; Points[11].y = -m;
	
}

void CAGD::Ellipse::Draw(HDC hdc)
{
	for (int i = 0; i < 4; i++)
	{
		if (i == 3)
		{
			Bezier[i].ReadPoint(Points + i * 3);
			Bezier[3].Points[3] = Points[0];

			Bezier[i].Draw(hdc);
			//Bezier[i].DrawControlPolygon(hdc);

		}
		else
		{
			Bezier[i].ReadPoint(Points + i * 3);
			Bezier[i].Draw(hdc);
			//Bezier[i].DrawControlPolygon(hdc);

		}

		
	}

}
