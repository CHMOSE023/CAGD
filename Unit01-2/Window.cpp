//#include "MainWindow.hpp"
//#include "TestLine.hpp"

//#include "CubicBezierCurve.hpp"
//#include "BezierDeCasteljau.hpp"
//
//#include "Bezier.hpp"

#include "BezierCurve.hpp"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

	//CubicBezierCurve cubicBezierCurve;
	//
	//P2D p2ds[4];
	//
	//p2ds[0].X = 100.0, p2ds[0].Y = 200.0;
	//p2ds[2].X = 200.0, p2ds[2].Y = 300.0;
	//p2ds[1].X = 600.0, p2ds[1].Y = 550.0;
	//p2ds[3].X = 700.0, p2ds[3].Y = 250.0;
	//
	//cubicBezierCurve.ReadPoint(p2ds);
	//
	//cubicBezierCurve.OnRun(nCmdShow);

	 //BezierDeCasteljau bezier;
	 //
	 //bezier.N = 7;
	 //bezier.Points[0] = P2D(100, 250);
	 //bezier.Points[1] = P2D(200, 450);
	 //bezier.Points[2] = P2D(300, 050);
	 //bezier.Points[3] = P2D(400, 450);
	 //bezier.Points[4] = P2D(500, 050);
	 //bezier.Points[5] = P2D(600, 450);
	 //bezier.Points[6] = P2D(700, 050);
	 //bezier.Points[7] = P2D(800, 250);
	 //
	 //
	 //bezier.OnRun(nCmdShow);
	
	 BezierCurve bezierCurve;
	 bezierCurve.OnRun(3); // 3 窗口最大化

	return 0;
}
