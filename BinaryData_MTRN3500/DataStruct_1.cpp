using namespace System;

#pragma pack(push, 1)
struct Data
{
	char C;//1 byte
	double A;//8 bytes
	float B;//4 bytes
};
#pragma pack(pop, 1)

int main()
{
	Console::WriteLine("Size of Data is: {0:D}", sizeof(Data));

	Console::ReadKey();

	return 0;
}