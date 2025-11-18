#using <System.dll>

using namespace System;
using namespace System::Threading;

void LiDAR();
void GNSS ();
bool Quit = false;

int main()
{
	Thread^ GNSSThread = gcnew Thread(gcnew ThreadStart(GNSS));
	Thread^ LiDARThread = gcnew Thread(gcnew ThreadStart(LiDAR));

	GNSSThread->Start();
	LiDARThread->Start();

	Console::ReadKey();
	Quit = true;
	Console::ReadKey();
	return 0;
}

void LiDAR()
{
	while (!Quit)
	{
		Console::WriteLine("Laser scan acquired");
		Thread::Sleep(10);
	}
}

void GNSS()
{
	while (!Quit)
	{
		Console::WriteLine("GNSS acquisition completed");
		Thread::Sleep(50);
	}
}