#include "UGV.h"

UGV::UGV(String^ serverIPAddress, int serverPort, String^ galilIPAddress, int galilPort)
{
	ServerIPAddress = serverIPAddress;
	GalilIPAddress = galilIPAddress;
	ServerPort = serverPort;
	GalilPort = galilPort;
	Watchdog = gcnew Stopwatch();
}

error_code UGV::ConnectAsServer()// Connect to laptop
{
	IncomingClient = Server->AcceptTcpClient();//blocking call
	IncomingClient->NoDelay = true;
	IncomingClient->ReceiveTimeout = 500;
	IncomingClient->SendTimeout = 500;
	IncomingClient->ReceiveBufferSize = 1024;
	IncomingClient->SendBufferSize = 1024;
	ServerStream = IncomingClient->GetStream();
	Watchdog->Start();
	return SUCCESS;
}

error_code UGV::StartServer()//Start Server in the internal computer so that laptop can connect to it
{
	IPAddress^ ServerAddress = IPAddress::Parse(ServerIPAddress);
	Server = gcnew TcpListener(ServerAddress, ServerPort);
	Server->Start();

	return SUCCESS;
}

error_code UGV::ConnectToGalil()// Connect to Galil
{
	Client = gcnew TcpClient(GalilIPAddress, GalilPort);
	Client->NoDelay = true;
	Client->ReceiveTimeout = 500;
	Client->SendTimeout = 500;
	Client->ReceiveBufferSize = 1024;
	Client->SendBufferSize = 1024;
	ClientStream = Client->GetStream();
	return SUCCESS;
}

error_code UGV::CommunicateWithGalil()
{
	String^ Drive;
	String^ Steer;
	array<String^>^ Fragments = Response->Split(' ');
	array<unsigned char>^ SendData = gcnew array<unsigned char>(128);
	SetSpeed = Convert::ToDouble(Fragments[1]);
	SetSteering = Convert::ToDouble(Fragments[2]);
	if (Flag != Convert::ToInt32(Fragments[3]))
	{
		Watchdog->Reset();
	}
	double OmegaLD = (1 + W / 2 / L * Math::Tan(SetSteering * Math::PI / 180.0)) * SetSpeed * CWheel / r;
	double OmegaRD = (1 - W / 2 / L * Math::Tan(SetSteering * Math::PI / 180.0)) * SetSpeed * CWheel / r;
	double Steering = SetSteering * CSteering / 360.0;

	if (WatchdogOK())
	{
		Drive = "JG " + OmegaLD.ToString("F0") + "," + OmegaRD.ToString("F0") + ";";
		Steer = "PS ,," + Steering.ToString("F0") + ";";
	}
	else
	{
		Drive = "JG 0,0;";
		Steer = "PS ,,0.0;";
	}
	SendData = Text::Encoding::ASCII->GetBytes(Drive);
	ClientStream->Write(SendData, 0, SendData->Length);
	SendData = Text::Encoding::ASCII->GetBytes(Steer);
	ClientStream->Write(SendData, 0, SendData->Length);

	//Check return response from Galil and generate a proper return value
	return SUCCESS;
}

int UGV::ReadEncoder()
{
	int Encoder;
	// YOu msut communicate with Galil and find the encoder value for example by sending QE commands
	// but for now let us assume that it is done and the value we got is 310 as shown below.
	Encoder = 310;

	return Encoder;
}

error_code UGV::CommunicateAsServer()
{
	// Read data from the client (laptop) and put the string into Response
	// Let us assume Response now contains the following as an example # <Speed> <Steering< Flag> #, with all fields
	// separated by a single space
	Response = "# 3.4 40.0 1 #";
	return SUCCESS;
}

bool UGV::WatchdogOK()
{
	// If the flag does not change for 128 ms, then watchdog will report false
	if (Watchdog->ElapsedMilliseconds > 128)
		return false;
	else
		return true;
}

bool UGV::IncomingClientConnected()
{
	return IncomingClient->Connected;
}

void UGV::IncomingClientClose()
{
	IncomingClient->Close();
}

UGV::~UGV()
{
	Client->Close();
	Server->Stop();
}