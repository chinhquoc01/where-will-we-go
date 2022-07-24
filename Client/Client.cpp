// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Common.h"
#include <string>
#include <WS2tcpip.h>
#include "Interface.h"
#include "../Shared/Enum.h"
#include "iostream"
#include "../Server/Location.h"

#define SERVER_PORT 5500 
#define SERVER_ADDR "127.0.0.1" 
#define BUFF_SIZE 2048 
#define SELECT_SIZE 128
#define SEPARATOR_CHAR "$"
#define END_MESS "\r\n"

using namespace std;

const ResponseCode responseCode;
const Message message;

vector<Location> locationList;


int main(int ardc, char *argv[])
{
	// Inittiate WinSock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData))
	{
		printf("Winsock 2.2. is not supported\n");
		return 0;
	}

	// Construct socket
	SOCKET client;
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == INVALID_SOCKET)
	{
		printf("Error %d: Cannot create client socket.", WSAGetLastError());
		return 0;
	}

	// Specify server address
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);

	// Request to connect server
	if (connect(client, (sockaddr *)&serverAddr, sizeof(serverAddr)))
	{
		printf("Error %d: Cannot connect server.", WSAGetLastError());
		return 0;
	}

	printf("Connected server!\n");

	// Comunicate with server

	int ret, messageLen;
	char buff[BUFF_SIZE], select_function[SELECT_SIZE];
	while (1) {
		UI_register_login(buff, select_function);
		if (strcmp(select_function, "3") == 0) break;
		else if (strcmp(select_function, "0") == 0) {
			system("cls");
			continue;
		}
		else {
			//gui username, password
			send(client, buff, strlen(buff), 0);

			//nhan thong diep
			char rcvbuff[BUFF_SIZE];
			ret = recv(client, buff, BUFF_SIZE, 0);
			buff[ret] = 0;

			getResponseCode(buff);
			Sleep(1000);
			if (strcmp(buff, responseCode.successLogin) == 0) {
				clientProcess(client, buff, select_function);
			}
		}
	}

	// Close socket
	closesocket(client);

	// Terminate Winsock
	WSACleanup();
	return 0;
}
