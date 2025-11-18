#include "Display.h"
#include <conio.h>
#include <LiDAR.h>

using namespace System;
using namespace System::Threading;

int main(void)
{
	SM_LiDAR^ SM_LMS151 = gcnew SM_LiDAR;
	LiDAR^ LMS151 = gcnew LiDAR(nullptr, SM_LMS151);
	Display^ MatlabGraph = gcnew Display(nullptr, SM_LMS151, nullptr);

	MatlabGraph->connect(DISPLAY_ADDRESS, 28000);

	LMS151->connect("192.168.0.1", 2111);

	while (!_kbhit())
	{
		LMS151->communicate();
		LMS151->processSharedMemory();
		MatlabGraph->communicate();
		Thread::Sleep(50);
	}

	Console::ReadKey();
	Console::ReadKey();

	return 0;
}