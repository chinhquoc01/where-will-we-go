// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include "../Shared/Enum.h"
#include "iostream"

#define SERVER_PORT 5500 
#define SERVER_ADDR "127.0.0.1" 
#define BUFF_SIZE 2048 
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

char buff[BUFF_SIZE];


string resolveResponseCode(string code) {
	const ResponseCode responseCode;
	if (code == responseCode.successRegister) {
		return "Register successfully";
	}
	else if (code == responseCode.errorExistedUsername) {
		return "Error: Account is already existed";
	}
	else if (code == responseCode.successLogin) {
		return "Login successfully";
	}
	else if (code == responseCode.errorInvalidAccount) {
		return "Error: Invalid account";
	}
	else if (code == responseCode.errorAlreadyLoggedIn) {
		return "Error: Account is already logged in";
	}
	else if (code == responseCode.successLogout) {
		return "Logout successfully";
	}
	else if (code == responseCode.errorUnauthorize) {
		return "Error: Unauthorize";
	}
	else {
		return "Cannot resolve response code: " + code;
	}
}

int main(int ardc, char* argv[])
{
	//Inittiate WinSock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		printf("Winsock 2.2. is not supported\n");
		return 0;
	}

	//Construct socket
	SOCKET client;
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == INVALID_SOCKET) {
		printf("Error %d: Cannot create client socket.", WSAGetLastError());
		return 0;
	}

	//Specify server address
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);

	//Request to connect server
	if (connect(client, (sockaddr *)&serverAddr, sizeof(serverAddr))) {
		printf("Error %d: Cannot connect server.", WSAGetLastError());
		return 0;
	}

	printf("Connected server!\n");

	//Comunicate with server

	int ret, messageLen;
	while (1) {
		//Send message 
		printf("Send to server: ");
		gets_s(buff, BUFF_SIZE);
		messageLen = strlen(buff);
		if (messageLen == 0) break;

		string message(buff);
		message += "\r\n";

		ret = send(client, message.c_str(), strlen(message.c_str()), 0);
		if (ret == SOCKET_ERROR)
			printf("Error %d: Cannot send data.", WSAGetLastError());
		//Receive echo message 
		ret = recv(client, buff, BUFF_SIZE, 0);
		if (ret == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAETIMEDOUT)
				printf("Time-out!");
			else printf("Error %d: Cannot receive data.", WSAGetLastError());
		}
		else if (strlen(buff) > 0) {
			buff[ret] = 0;
			string responseCode(buff);

			cout << "Receive from server: " << resolveResponseCode(responseCode) << endl;
		}
	}

	//Close socket 
	closesocket(client);

	//Terminate Winsock
	WSACleanup();
	return 0;
}

