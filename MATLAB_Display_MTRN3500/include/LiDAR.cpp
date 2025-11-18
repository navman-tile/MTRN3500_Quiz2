#include <LiDAR.h>
#include <SMObjects.h>

LiDAR::LiDAR(SM_ThreadManagement^ SM_TM, SM_LiDAR^ SM_lidar)
{
	UGV_SM_TM_ = SM_TM;
	LiDAR_SM_LiDAR_ = SM_lidar;
}

// Send/Recieve data from shared memory structures
error_state LiDAR::processSharedMemory()
{
	return SUCCESS;
}

// Shutdown all modules in the software
void LiDAR::shutdownModules()
{

}

// Get Shutdown signal for module, from Thread Management SM
bool LiDAR::getShutdownFlag()
{
	return true;
}

// Thread function for TMM
void LiDAR::threadFunction()
{

}

error_state LiDAR::connect(String^ hostName, int portNumber)
{
	Client = gcnew TcpClient(hostName, portNumber);
	Stream = Client->GetStream();
	Client->NoDelay = true;
	Client->ReceiveTimeout = 500;
	Client->SendTimeout = 500;
	Client->ReceiveBufferSize = 1024;
	Client->SendBufferSize = 1024;

	SendData = gcnew array<unsigned char>(512);
	ReadData = gcnew array<unsigned char>(8192);

	//Step 1: Authorise to change the configuration
	String^ authorCmd = "sMN SetAccessMode 03 F4724744";
	SendData = Encoding::ASCII->GetBytes(authorCmd);
	Stream->WriteByte(0x02);
	Stream->Write(SendData, 0, SendData->Length);
	Stream->WriteByte(0x03);
	System::Threading::Thread::Sleep(100);

	int len = Stream->Read(ReadData, 0, ReadData->Length);
	String^ resp = Encoding::ASCII->GetString(ReadData, 0, len);
	Console::WriteLine("Auth response:\n{0}", resp);

	// Step 2: Configure scan frequency, angle, and resolution
	String^ scanCfg = "sMN mLMPsetscancfg +5000 +1 +5000 +0 +1800000";
	SendData = Encoding::ASCII->GetBytes(scanCfg);
	Stream->WriteByte(0x02);
	Stream->Write(SendData, 0, SendData->Length);
	Stream->WriteByte(0x03);
	Thread::Sleep(100);

	len = Stream->Read(ReadData, 0, ReadData->Length);
	resp = Encoding::ASCII->GetString(ReadData, 0, len);
	Console::WriteLine("Scan config response:\n{0}", resp);

	// Step 3: Configure LiDAR to output only DIST1 channel
	String^ dataCfg = "sWN LMDscandatacfg 01 00 0 0 0 00 00 0 0 0 0 +1";
	SendData = Encoding::ASCII->GetBytes(dataCfg);
	Stream->WriteByte(0x02);
	Stream->Write(SendData, 0, SendData->Length);
	Stream->WriteByte(0x03);
	Thread::Sleep(100);

	len = Stream->Read(ReadData, 0, ReadData->Length);
	resp = Encoding::ASCII->GetString(ReadData, 0, len);
	Console::WriteLine("Channel config response:\n{0}", resp);

	return SUCCESS;
}

error_state LiDAR::communicate()
{
	//sRN LMDscandata
	// Sending 0x02
	// Sending "sRN LMDscandata"
	// Sending 0x03

	String^ Command = "sRN LMDscandata";
	SendData = Encoding::ASCII->GetBytes(Command);
	Stream->WriteByte(0x02);
	Stream->Write(SendData, 0, SendData->Length);
	Stream->WriteByte(0x03);
	Thread::Sleep(100);

	Stream->Read(ReadData, 0, ReadData->Length);
	String^ Response = Encoding::ASCII->GetString(ReadData);
	Console::WriteLine(Response);
	Console::WriteLine();

	return SUCCESS;
}

