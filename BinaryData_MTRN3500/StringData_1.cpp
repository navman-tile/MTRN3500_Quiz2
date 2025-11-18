using namespace System;

int main()
{
	double Temperature;
	String^ Response = "Room1 temperature is 23.5 degrees";

	array<wchar_t>^ Space = { ' ' };
	array<String^>^ SubStringList = Response->Split(Space);

	for (int i = 0; i < SubStringList->Length; i++)
	{
		Console::WriteLine(SubStringList[i]);
	}

	Temperature = Convert::ToDouble(SubStringList[3]);
	Console::WriteLine("The temperature is {0:F3} degrees", Temperature);

	Console::ReadKey();

	return 0;

}