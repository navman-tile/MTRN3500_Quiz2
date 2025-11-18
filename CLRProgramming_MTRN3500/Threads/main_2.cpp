#using <System.dll>

using namespace System;
using namespace System::Threading;

ref class OurThreads
{
	static Barrier^ ThreadBarrier;

public:
	static bool Quit;

	OurThreads()
	{
		ThreadBarrier = gcnew Barrier(2);
		Quit = false;
	}

	static void LiDAR()
	{
		Console::WriteLine("Enter LiDAR routine");
		Thread::Sleep(5000);
		Console::WriteLine("LiDAR ready");

		ThreadBarrier->SignalAndWait();
		
		while (!Quit)
		{
			Console::WriteLine("Laser scan acquired");
			Thread::Sleep(50);
		}
	}

	static void GNSS()
	{
		Console::WriteLine("Enter GNSS routine");
		Thread::Sleep(1000);
		Console::WriteLine("GNSS ready");

		ThreadBarrier->SignalAndWait();

		while (!Quit)
		{
			Console::WriteLine("GNSS acquisition completed");
			Thread::Sleep(50);
		}
	}

};

int main()
{
	OurThreads^ VehicleThreads = gcnew OurThreads;
	Thread^ GNSSThread = gcnew Thread(gcnew ThreadStart(&OurThreads::GNSS));
	Thread^ LiDARThread = gcnew Thread(gcnew ThreadStart(&OurThreads::LiDAR));

	GNSSThread->Start();
	LiDARThread->Start();

	Console::ReadKey();
	OurThreads::Quit = true;
	Console::ReadKey();
	return 0;
}

