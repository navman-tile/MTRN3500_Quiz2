#pragma once
#using <System.dll>

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Diagnostics;

enum error_code
{
	SUCCESS,
	ERR_CLIENT_CONNECTION_FAILED,
	ERR_SERVER_CONNECTION_FAAILED,
	ERR_NO_CLIENT_DATA,
	ERR_NO_SERVER_DATA
};

constexpr double L = 0.80; // UGV length (wheel base) in meters
constexpr double W = 0.60; // UGV width (wheel track) in meters
constexpr double r = 0.21; // UGV wheel radius in meters
constexpr int CWheel = 8192; // counts per revolution of a wheel
constexpr int CSteering = 4096; // counts per revolution of the steering motor

ref class UGV
{
	TcpListener^ Server;
	String^ ServerIPAddress;
	int ServerPort;
	NetworkStream^ ServerStream;
	TcpClient^ Client;
	String^ GalilIPAddress;
	int GalilPort;
	NetworkStream^ ClientStream;
	TcpClient^ IncomingClient;
	Stopwatch^ Watchdog;
	String^ Response;
	double SetSpeed;
	double SetSteering;
	int Flag;
public:
	UGV() {};
	UGV(String^ serverIPAddress, int serverPort, String^ clientIPAddress, int clientPort);
	error_code ConnectAsServer();
	error_code StartServer();
	error_code ConnectToGalil();
	error_code CommunicateWithGalil();
	int ReadEncoder();
	error_code CommunicateAsServer();
	bool WatchdogOK();
	bool IncomingClientConnected();
	void IncomingClientClose();
	~UGV();
};
