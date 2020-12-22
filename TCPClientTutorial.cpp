// TCPClientTutorial.cpp : Defines the entry point for the application.
//

#include "TCPClientTutorial.h"
#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	// We need the information from the server side so we know where to connect to
	string ipAddress = "127.0.0.1"; // Connecting to local host's ip address, Local machine ip4: "127.0.0.1"
	int port = 54000; // Listening port # from server application

	// Initialize WinSock
	WSAData data; // This'll hold our socket information
	WORD ver = MAKEWORD(2, 2); // Version 2.2
	int wsResult = WSAStartup(ver, &data); // Starts up the port stuff (Version, info about implementation information)
	if (wsResult != 0) {
		cerr << "Can't start Winsock, Err #: " << wsResult << endl;
		return 1;
	}

	// Create Socket
	SOCKET sock = socket(AF_INET /*A family of addresses, ipv4*/, SOCK_STREAM /*tcp*/, 0 /*flag?*/);
	if (sock == INVALID_SOCKET) {
		cerr << "Can't create socket, Err #: " << WSAGetLastError() << endl;
		WSACleanup(); // If failed, clean this 
		return 2;
	}

	// Fill in hint structure
	// This will hold the server side information, so we can connect to it
	sockaddr_in hint; 
	hint.sin_family = AF_INET; // This is ip-4 address
	hint.sin_port = htons(port); // Give it the port number (have to convert it to network byte ordering, big endian)
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr); // Also give hint our ipAddress in ip-4 format in big endian format

	// Connect to Server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint)); // Connect our socket to the hint location
	if (connResult == SOCKET_ERROR) {
		cerr << "Can't connect to server, Err #: " << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return 3;
	}

	// Do-While loop to send and receive data
	char  buf[4096];
	string userInput;

	do {
		// Prompt the user for some text
		cout << "Gimme text: ";
		getline(cin, userInput);

		if (userInput.size() > 0) {
			// Send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);

			if (sendResult != SOCKET_ERROR) {
				// Wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);

				if (bytesReceived > 0) {
					// Echo for response
					cout << "SERVER: " << string(buf, 0, bytesReceived) << endl;
				}
			}
		}

	} while (userInput.size() > 0);

	//Gracefully close down everything
	closesocket(sock);
	WSACleanup();

	return 0;
}
