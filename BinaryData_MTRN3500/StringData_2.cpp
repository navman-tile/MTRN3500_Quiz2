using namespace System;

int main()
{
	int Range;
	String^ Response = "Range data is 15EF mm";

	//array<wchar_t>^ Space = { ' ' };
	//array<String^>^ SubStringList = Response->Split(Space);

	array<String^>^ SubStringList = Response->Split(' ');

	for (int i = 0; i < SubStringList->Length; i++)
	{
		Console::WriteLine(SubStringList[i]);
	}

	Range = Convert::ToInt32(SubStringList[3], 16);
	Console::WriteLine("The range is {0:F3} mm", Range);

	Console::ReadKey();

	return 0;

}