#include "MainWindow.hpp"
#include "TestLine.hpp"
#include "p2d.h"
#include "CubicBezierCurve.hpp"
#include "Bezier.hpp"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	 CubicBezierCurve cubicBezierCurve;
	 
	 //P2D p2ds[4];
	 //
	 //p2ds[0].X = 100.0, p2ds[0].Y = 200.0;
	 //p2ds[2].X = 200.0, p2ds[2].Y = 300.0;
	 //p2ds[1].X = 600.0, p2ds[1].Y = 550.0;
	 //p2ds[3].X = 700.0, p2ds[3].Y = 250.0;	
	 
	 //cubicBezierCurve.ReadPoint(p2ds);

	 // cubicBezierCurve.OnRun(nCmdShow);

	 Bezier bezier;

	 bezier.N = 4; // n=3
	 bezier.P2ds.resize(8);
	 bezier.P2ds[0] = P2D(100, 250);
	 bezier.P2ds[1] = P2D(200, 450);
	 bezier.P2ds[2] = P2D(300, 050);
	 bezier.P2ds[3] = P2D(400, 450);
	 bezier.P2ds[4] = P2D(500, 050);
	 bezier.P2ds[5] = P2D(600, 450);
	 bezier.P2ds[6] = P2D(700, 050);
	 bezier.P2ds[7] = P2D(800, 250);

	 bezier.OnRun(nCmdShow);
	
	

	return 0;
}
