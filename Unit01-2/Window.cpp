#include "MainWindow.hpp"
#include "DrewLine.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{

    DrewLine drewLine;
    drewLine.OnRun(nCmdShow);

    return 0;
}

