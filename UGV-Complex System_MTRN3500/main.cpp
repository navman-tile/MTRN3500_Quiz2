#include "UGV.h"

int main()
{
	bool UGVOn = true;
	//instantiate a UGV object
	UGV^ Weeder = gcnew UGV("192.168.1.200", 25000, "192.168.0.100", 30000);
	//connect to galil
	Weeder->ConnectToGalil();
	//Start the server 
	Weeder->StartServer();
	// while UGV is on
	while (UGVOn)
	{
		//Listen to an incoming connection
		//Establish a connection
		Weeder->ConnectAsServer();
		//while (connected to external laptop client)
		while (Weeder->IncomingClientConnected())
		{
			//Receive data from the client and extract setspeed and set steering
			//Read Steering encoder
			//calculate left wheel speed, right wheel speed in cts/s and steering in counts
			//If Watchdog is ok
			// Send commands to galil
			//else
				// Send zero commands to Galil
			Weeder->CommunicateWithGalil();
		// end - while (connected to external laptop client)
		}
	// close incoming client
		Weeder->IncomingClientClose();
	// end - while UGV is on
	}

	// Stop Server
	// Close Galil Client

	return 0;
}