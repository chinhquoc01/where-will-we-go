// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include "vector"
#include "../Shared/Enum.h"
#include "../Server/Account.h"
#include "../Server/Common.h"
#include "../Server/Location.h"
#include <iostream>
#include <fstream>
#include "conio.h"

#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048
#define SELECT_SIZE 128
#define SEPARATOR_CHAR "$"
#define END_MESS "\r\n"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

char buff[BUFF_SIZE];
char select_function[SELECT_SIZE];

const ResponseCode responseCode;
const Message message;

vector<Location> locationList;

/*
* @function split: split string by delim character
*
* @param string: string want to split
*
* @param delim: character to split
*
* @return: array string after split
*/
vector<string> split(const string &s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

void recvLocationData(SOCKET client) {

	int ret;

	ret = recv(client, buff, BUFF_SIZE, 0);
	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT)
			printf("Time-out!");
		else printf("Error %d: Cannot receive data.", WSAGetLastError());
	}
	else if (strlen(buff) > 0) {
		buff[ret] = 0;
		printf("Receive from server: %s\n", buff);
	}
	string responseCodeGetLocation(buff);
	if (responseCodeGetLocation == responseCode.successGetLocation) {
		ret = recv(client, buff, BUFF_SIZE, 0);
		if (ret == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAETIMEDOUT)
				printf("Time-out!");
			else printf("Error %d: Cannot receive data.", WSAGetLastError());
		}
		else if (strlen(buff) > 0) {
			buff[ret] = 0;
			printf("Receive from server: %s\n", buff);
		}

		string strLength(buff);
		int length = stoi(strLength);
		for (int i = 0; i < length; i++) {

			ret = recv(client, buff, BUFF_SIZE, 0);
			if (ret == SOCKET_ERROR) {
				if (WSAGetLastError() == WSAETIMEDOUT)
					printf("Time-out!");
				else printf("Error %d: Cannot receive data.", WSAGetLastError());
			}
			else if (strlen(buff) > 0) {
				buff[ret] = 0;
				string response(buff);
				cout << response << endl;
				vector<string> messageData = split(response, '$');
				if (messageData.size() < 5) {
					printf("Error when get list location.");
					break;
				}
			}
		}

		getch();
	}
}

// input username ,password
void input()
{
	char temp[BUFF_SIZE];

	system("cls");

	if (strcmp(select_function, "1") == 0)
	{
		strcpy(buff, message.REGISTER);
		strcat(buff, SEPARATOR_CHAR);
		printf("REGISTER\n");
	}

	else if (strcmp(select_function, "2") == 0)
	{
		strcpy(buff, message.LOGIN);
		strcat(buff, SEPARATOR_CHAR);
		printf("LOGIN\n");
	}

	printf("Username: ");
	fflush(stdin);
	gets_s(temp, BUFF_SIZE);
	strcat(buff, temp);
	strcat(buff, SEPARATOR_CHAR);

	printf("Password: ");
	fflush(stdin);
	gets_s(temp, BUFF_SIZE);
	strcat(buff, temp);
	strcat(buff, END_MESS);
}

// Giao dien dang ky dang nhap
void register_login(SOCKET client)
{
	system("cls");

	printf("---------------------------------------------\n");
	printf("| NUMBER|             FUNCTION              |\n");
	printf("---------------------------------------------\n");
	printf("|   1   | Register                          |\n");
	printf("---------------------------------------------\n");
	printf("|   2   | Login                             |\n");
	printf("---------------------------------------------\n");
	printf("|   3   | Exit                              |\n");
	printf("---------------------------------------------\n");

	/*printf("1. Register\n");
	printf("2. Login\n");
	printf("3. Exit\n");*/

	printf("Enter number to select function: ");
	fflush(stdin);
	gets_s(select_function, SELECT_SIZE);

	if (strcmp(select_function, "1") == 0 || strcmp(select_function, "2") == 0)
	{
		input();
		// gui username, password
		send(client, buff, strlen(buff), 0);
	}

	else if (strcmp(select_function, "3") == 0)
	{
	}
	else
	{
		printf("Function doesn't exist\n");
		strcpy(select_function, "0");
	}
}

// Giao dien cac chuc nang
void clientProcess(SOCKET client)
{
	system("cls");

	while (1)
	{
		if (strcmp(select_function, "7") == 0)
			break;

		system("cls");
		printf("---------------------------------------------\n");
		printf("| NUMBER|             FUNCTION              |\n");
		printf("---------------------------------------------\n");
		printf("|   1   | See list of location              |\n");
		printf("---------------------------------------------\n");
		printf("|   2   | See list of favourite location    |\n");
		printf("---------------------------------------------\n");
		printf("|   3   | Add new location                  |\n");
		printf("---------------------------------------------\n");
		printf("|   4   | See shared list                   |\n");
		printf("---------------------------------------------\n");
		printf("|   5   | Backup                            |\n");
		printf("---------------------------------------------\n");
		printf("|   6   | Restore                           |\n");
		printf("---------------------------------------------\n");
		printf("|   7   | Logout                            |\n");
		printf("---------------------------------------------\n");

		/*printf("1. See list of location\n");
		printf("2. See list of favourite location\n");
		printf("3. Add new location\n");
		printf("4. See shared list\n");
		printf("5. Backup\n");
		printf("6. Restore\n");
		printf("7. Logout\n");*/

		printf("Enter number to select function: ");
		fflush(stdin);
		gets_s(select_function, SELECT_SIZE);

		int key = atoi(select_function);
		switch (key)
		{
		case 1:
		{
			system("cls");

			while (1)
			{
				system("cls");
				printf("See list of location\n");
				printf("---------------------------------------------\n");
				printf("| IDType|             FUNCTION              |\n");
				printf("---------------------------------------------\n");
				printf("|   1   | Restaurant                        |\n");
				printf("---------------------------------------------\n");
				printf("|   2   | Coffee                            |\n");
				printf("---------------------------------------------\n");
				printf("|   3   | Cinema                            |\n");
				printf("---------------------------------------------\n");
				printf("|   4   | Fashion shop                      |\n");
				printf("---------------------------------------------\n");
				printf("|   *   | All location                      |\n");
				printf("---------------------------------------------\n");
				printf("|   0   | Comeback                          |\n");
				printf("---------------------------------------------\n");

				/*printf("Select type of list location\n");
				printf("1. Restaurant\n");
				printf("2. Coffee\n");
				printf("3. Cinema\n");
				printf("4. Fashion shop\n");
				printf("*. All location\n");
				printf("0. Comeback\n");*/

				printf("Enter number to select IDType: ");
				fflush(stdin);
				gets_s(select_function, SELECT_SIZE);
				if (strcmp(select_function, "0") == 0)
					break;
				strcpy(buff, message.GET);
				strcat(buff, SEPARATOR_CHAR);
				strcat(buff, select_function);
				strcat(buff, END_MESS);

				send(client, buff, strlen(buff), 0);

				// recv
				recvLocationData(client);
			}
			break;
		}
		case 2:
		{
			system("cls");

			while (1)
			{
				system("cls");

				printf("See list of favourite location\n");
				printf("---------------------------------------------\n");
				printf("| IDType|             FUNCTION              |\n");
				printf("---------------------------------------------\n");
				printf("|   1   | Restaurant                        |\n");
				printf("---------------------------------------------\n");
				printf("|   2   | Coffee                            |\n");
				printf("---------------------------------------------\n");
				printf("|   3   | Cinema                            |\n");
				printf("---------------------------------------------\n");
				printf("|   4   | Fashion shop                      |\n");
				printf("---------------------------------------------\n");
				printf("|   *   | All location                      |\n");
				printf("---------------------------------------------\n");
				printf("|   0   | Comeback                          |\n");
				printf("---------------------------------------------\n");

				/*printf("Select IDType of list location\n");
				printf("1. Restaurant\n");
				printf("2. Coffee\n");
				printf("3. Cinema\n");
				printf("4. Fashion shop\n");
				printf("*. All location\n");
				printf("0. Comeback\n");*/

				printf("Enter number to select IDType: ");
				fflush(stdin);
				gets_s(select_function, SELECT_SIZE);
				if (strcmp(select_function, "0") == 0)
					break;
				strcpy(buff, message.GETFAVOURITE);
				strcat(buff, SEPARATOR_CHAR);
				strcat(buff, select_function);
				strcat(buff, END_MESS);

				send(client, buff, strlen(buff), 0);

				// recv
			}
			break;
		}
		case 3:
		{
			system("cls");

			strcpy(buff, "ADD");
			strcat(buff, SEPARATOR_CHAR);
			char inp[BUFF_SIZE];
			printf("Add new location\n");
			printf("(IDtype) Restaurant : 1, Coffee: 2, Cinema: 3, Fashion shop: 4\n");
			printf("Name: ");
			fflush(stdin);
			gets_s(inp);
			strcat(buff, inp);

			printf("IDType: ");
			fflush(stdin);
			gets_s(inp);
			strcat(buff, inp);

			printf("Address: ");
			fflush(stdin);
			gets_s(inp);
			strcat(buff, inp);

			printf("Description: ");
			fflush(stdin);
			gets_s(inp);
			strcat(buff, inp);
			strcat(buff, END_MESS);

			send(client, buff, strlen(buff), 0);

			recv(client, buff, BUFF_SIZE, 0);
			if (strcmp(buff, responseCode.successAdd) == 0)
			{
				printf("Add new location successfull\n");
				Sleep(1000);
			}
			else if (strcmp(buff, responseCode.errorInvalidInput) == 0)
			{
				printf("You haven't input enough infomation!\n");
				Sleep(1000);
			}
			else if (strcmp(buff, responseCode.errorNotExistType) == 0)
			{
				printf("IDType doesn't existed!\n");
				Sleep(1000);
			}
		}
		break;
		case 4:
		{
			system("cls");

			strcpy(buff, message.GETSHARELIST);
			strcat(buff, END_MESS);

			send(client, buff, strlen(buff), 0);

			// recv
		}
		break;
		case 5:
		{
			system("cls");

			strcpy(buff, message.BACKUP);
			strcat(buff, END_MESS);

			send(client, buff, strlen(buff), 0);

			recv(client, buff, BUFF_SIZE, 0);
			if (strcmp(buff, responseCode.successBackup) == 0)
			{
				printf("Backup successfull\n");
				Sleep(1000);
			}
		}
		break;
		case 6:
		{
			system("cls");

			strcpy(buff, message.RESTORE);
			strcat(buff, END_MESS);

			send(client, buff, strlen(buff), 0);

			recv(client, buff, BUFF_SIZE, 0);
			if (strcmp(buff, responseCode.successRestore) == 0)
			{
				printf("Restore successfull\n");
				Sleep(1000);
			}

			else if (strcmp(buff, responseCode.errorNoBackup) == 0)
			{
				printf("Account hasn't been backup!\n");
				Sleep(1000);
			}
		}
		break;
		case 7:
		{
			system("cls");

			strcpy(buff, message.LOGOUT);
			strcat(buff, END_MESS);

			send(client, buff, strlen(buff), 0);

			recv(client, buff, BUFF_SIZE, 0);
			if (strcmp(buff, responseCode.successLogout) == 0)
			{
				printf("Logout successfull\n");
				Sleep(1000);
			}
		}
		break;
		default:
			printf("Function doesn't exist\n");
			Sleep(1000);
		}
	}
}


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
	while (1)
	{
		/*
		register_login(client);
		if (strcmp(select_function, "3") == 0)
			break;
		else if (strcmp(select_function, "0") == 0)
		{
			system("cls");
			continue;
		}
		else
		{
			// nhan thong diep
			char rcvbuff[BUFF_SIZE];
			ret = recv(client, buff, BUFF_SIZE, 0);
			buff[ret] = 0;

			if (strcmp(buff, responseCode.successRegister) == 0)
			{
				printf("Register successfull!\n");
				Sleep(1000);
				continue;
			}
			else if (strcmp(buff, responseCode.errorExistedUsername) == 0)
			{
				printf("Username doesn't existed!\n");
				Sleep(1000);
				continue;
			}
			else if (strcmp(buff, responseCode.invalidMessage) == 0)
			{
				printf("Message isn't determined!\n");
				Sleep(1000);
				continue;
			}
			else if (strcmp(buff, responseCode.successLogin) == 0)
			{
				printf("Login successfull!\n");
				Sleep(1000);
				clientProcess(client);
				continue;
			}
			else
			{
				printf("Username or password is wrong!\n");
				Sleep(1000);
				continue;
			}
		}*/

		/*
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
			printf("Receive from server: %s\n", buff);
		}
		*/

		
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
		printf("Receive from server: %s\n", buff);
		}
	

	}

	// Close socket
	closesocket(client);

	// Terminate Winsock
	WSACleanup();
	return 0;
}
