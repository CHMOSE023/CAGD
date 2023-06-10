#include "MainWindow.hpp"
#include "TestLine.hpp"
#include "p2d.h"
#include "CubicBezierCurve.hpp"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	// CubicBezierCurve cubicBezierCurve;
	// 
	// P2D p2ds[4];
	// 
	// p2ds[0].X = 100.0, p2ds[0].Y = 200.0;
	// p2ds[1].X = 300.0, p2ds[1].Y = 500.0;
	// p2ds[2].X = 500.0, p2ds[2].Y = 550.0;
	// p2ds[3].X = 700.0, p2ds[3].Y = 250.0;	
	// 
	// cubicBezierCurve.ReadPoint(p2ds);
	// cubicBezierCurve.OnRun(nCmdShow);
	// 

	TestLine testLine;

	testLine.OnRun(nCmdShow);

	return 0;
}
