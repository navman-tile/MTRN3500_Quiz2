using namespace System;

#pragma pack(push, 4)
struct GNSS
{
	unsigned int Header; // 4 bytes 0xAA 0x44 0x12 0x1C
	unsigned char Discard1[40];
	double Northing;
	double Easting;
	double Height;
	unsigned char Discard2[40];
	unsigned int CRC;
};
#pragma pack(pop, 4)

int main()
{
	Console::WriteLine("Size of Data is: {0:D}", sizeof(GNSS));

	Console::ReadKey();

	return 0;
}