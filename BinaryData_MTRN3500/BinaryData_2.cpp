using namespace System;

int main()
{
	double A = 12345.54321; //MSbyte 40 C8 1C C5 87 E7 C0 6E LSByte

	unsigned char Data[8] = { 0x6E, 0xC0, 0xE7, 0x87, 0xC5, 0x1C, 0xC8, 0x40 };

	double B;

	Console::WriteLine("B is: {0:F5} ", B);

	unsigned char* BytePtr = (unsigned char*)&B;

	for (int i = 0; i < sizeof(double); i++)
	{
		*(BytePtr+i) = Data[i];
	}

	Console::WriteLine("A is: {0:F5} ", A);
	Console::WriteLine("B is: {0:F5} ", B);

	Console::ReadKey();
	return 0;
}