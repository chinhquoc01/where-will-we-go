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
#define SERVER_PORT 5500 
#define SERVER_ADDR "127.0.0.1" 
#define BUFF_SIZE 2048 
#define SELECT_SIZE 128
#define SEPARATOR_CHAR "$"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

char buff[BUFF_SIZE];
char select[SELECT_SIZE];

const ResponseCode responseCode;
const Message message;


//input username ,password
void input() {
	char temp[BUFF_SIZE];

	system("cls");

	if (strcpy(select, "1")) {
		strcpy(buff, message.REGISTER);
		strcat(buff, SEPARATOR_CHAR);
		printf("REGISTER\n");
	}

	else if (strcpy(select, "2")) {
		strcpy(buff, message.LOGIN);
		strcat(buff, SEPARATOR_CHAR);
		printf("LOGIN\n");
	}

	printf("Account: \n");
	fflush(stdin);
	gets_s(temp, BUFF_SIZE);
	strcat(buff, temp);
	strcat(buff, SEPARATOR_CHAR);

	printf("Password: \n");
	fflush(stdin);
	gets_s(temp, BUFF_SIZE);
	strcat(buff, temp);
}

//Giao dien dang ky dang nhap
void register_login(SOCKET client, int ret) {
	
	printf("1. Register\n");
	printf("2. Login\n");
	printf("3. Exit\n");

	printf("Enter number to select function: ");
	fflush(stdin);
	gets_s(select, SELECT_SIZE);

	if (strcmp(select, "1") == 0 || strcmp(select, "2") == 0) {
		
		input();
		//gui username, password
		send(client, buff, strlen(buff), 0);
	}

	else if (strcmp(select, "3")) {	}
	else {
		printf("Function doesn't exist\n");
		strcpy(select, "0");
	}
}

//Giao dien cac chuc nang
void function(SOCKET client) {
	while (1) {
		printf("1. See list of location\n");
		printf("2. See list of favourite location\n");
		printf("3. Add new location\n");
		printf("4. See shared list\n");
		printf("5. Backup\n");
		printf("6. Restore\n");
		printf("7. Logout\n");

		printf("Enter number to select function: ");
		fflush(stdin);
		gets_s(select, SELECT_SIZE);

		int key = atoi(select);
		switch (key) {
		case 1: {
			system("cls");
			while (1) {
				printf("Select type of list location\n");
				printf("1. Restaurant\n");
				printf("2. Coffee\n");
				printf("3. Cinema\n");
				printf("4. Fashion shop\n");
				printf("*. All location\n");
				printf("0. Comeback\n");
				fflush(stdin);
				gets_s(select, SELECT_SIZE);
				if (strcpy(select, "0")) break;
				strcpy(buff, message.GET);
				strcat(buff, SEPARATOR_CHAR);
				strcat(buff, select);

				send(client, buff, strlen(buff), 0);

				//recv
			} break;
		}
		case 2: {
			system("cls");
			while (1) {
				printf("Select type of list location\n");
				printf("1. Restaurant\n");
				printf("2. Coffee\n");
				printf("3. Cinema\n");
				printf("4. Fashion shop\n");
				printf("*. All location\n");
				printf("0. Comeback\n");
				fflush(stdin);
				gets_s(select, SELECT_SIZE);
				if (strcpy(select, "0")) break;
				strcpy(buff, message.GETFAVOURITE);
				strcat(buff, SEPARATOR_CHAR);
				strcat(buff, select);

				send(client, buff, strlen(buff), 0);

				//recv
			} break;
		}
		case 3: {
			system("cls");
		}
		case 4: {
			system("cls");
		}
		case 5: {
			system("cls");
		}
		case 6: {
			system("cls");
		}
		case 7: {

		}
		default:
			printf("Function doesn't exist\n");
		}
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
		register_login(client, ret);
		if (strcpy(select, "3")) break;
		else if (strcpy(select, "0")) {
			system("cls");
			continue;
		}
		else {
			//nhan thong diep
			ret = recv(client, buff, BUFF_SIZE, 0);
			buff[ret] = 0;

			if (strcpy(buff, responseCode.successRegister)) {
				printf("Register successfull!\n"); continue;
			}
			else if (strcpy(buff, responseCode.errorExistedUsername)) {
				printf("Existed Username!\n"); continue;
			}
			/*else {
			printf("Chua nhap du thong tin");
			}*/
			if (strcpy(buff, responseCode.successLogin)) {
				printf("Login successfull!\n");
				function(client);
			}
			else {
				printf("Username or password is wrong!\n"); continue;
			}

		}

		//Send message 
		printf("Send to server: ");
		gets_s(buff, BUFF_SIZE);
		messageLen = strlen(buff);
		if (messageLen == 0) break;

		ret = send(client, buff, messageLen, 0);
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

	//Close socket 
	closesocket(client);

	//Terminate Winsock
	WSACleanup();
	return 0;
}

