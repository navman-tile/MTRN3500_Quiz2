#using <System.dll>

using namespace System;
using namespace System::IO;

ref struct GNSS
{
	double Lattitude;
	double Longitude;
	GNSS(double lat, double lng) : Lattitude(lat), Longitude(lng) {}
};

int main()
{
	String^ Filename = "GNSS.m";
	StreamWriter^ sw = gcnew StreamWriter(Filename);

	array<GNSS^>^ GNSSData = gcnew array<GNSS^>{ gcnew GNSS(13, 28), gcnew GNSS(2, 4), gcnew GNSS(5, 6), gcnew GNSS(7, 8), gcnew GNSS(9, 10), gcnew GNSS(11, 12) };

	for (int i = 0; i < GNSSData->Length; i++)
	{
		sw->WriteLine("{0, 10:F3} {1, 10:F3}", GNSSData[i]->Lattitude, GNSSData[i]->Longitude);
	}
	sw->Close();

	Console::ReadKey();
	return 0;
}