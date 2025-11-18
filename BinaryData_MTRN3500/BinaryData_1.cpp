using namespace System;

int main()
{
	double A = 12345.54321; //MSbyte 40 C8 1C C5 87 E7 C0 6E LSByte
	unsigned char* BytePtr = (unsigned char*)&A;
	//unsigned long long* BytePtr = (unsigned long long*)&A;

	for (int i = 0; i < sizeof(double); i++)
	{
		Console::Write("{0:X} ", *BytePtr++);
	}

	Console::ReadKey();
	return 0;
}