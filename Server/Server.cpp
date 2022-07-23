// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "ws2tcpip.h"
#include "winsock2.h"
#include "process.h"
#include "iostream"
#include <fstream>
#include "Common.h"
#include "Account.h"
#include "LocationService.h"
#include "../Shared/Enum.h"

#pragma comment (lib,"ws2_32.lib")

#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048

int clientPort;
char clientIP[INET_ADDRSTRLEN];
SOCKET sock[4048];
SOCKET connSock;

const string accountStore = "accounts.json";
const string locationStore = "locations.json";

const ResponseCode responseCode;


/* userThread - Thread to receive the user message from client*/
unsigned __stdcall userThread(void *param) {
	char buff[BUFF_SIZE];
	int ret;
	SOCKET connectedSocket = (SOCKET)param;
	for(int i=0; sock[i] != INVALID_SOCKET, i++) {

	}


	while (1) {
		ret = recv(connectedSocket, buff, BUFF_SIZE, 0);
		if (ret == SOCKET_ERROR) {
			printf("Error %d: Cannot receive data from client[%s:%d]\n", WSAGetLastError(), clientIP, clientPort);
			break;
		}

		else if (strlen(buff) > 0) {
			buff[ret] = '\0';

			// Send response to client
			ret = send(connectedSocket, buff, strlen(buff), 0);
			if (ret == SOCKET_ERROR) {
				printf("Error %d: Cannot send data to client[%s:%d]\n", WSAGetLastError(), clientIP, clientPort);
				break;
			}
		}
	}

	closesocket(connectedSocket);
	return 0;
}


int main(int argc, char* argv[])
{
	//Initiate WinSock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		printf("Winsock 2.2 is not supported\n");
		return 0;
	}

	//Construct socket	
	SOCKET listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//Bind address to socket
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);
	if (::bind(listenSock, (sockaddr *)&serverAddr, sizeof(serverAddr)))
	{
		printf("Error %d: Cannot associate a local address with server socket.", WSAGetLastError());
		return 0;
	}

	//Listen request from client
	if (listen(listenSock, 10)) {
		printf("Error %d: Cannot place server socket in state LISTEN.", WSAGetLastError());
		return 0;
	}

	printf("Server started!\n");
	
	// Demo ghi ra file json
	vector<Account> accounts;
	for (int i = 0; i < 5; i++)
	{
		Account a("user" + to_string(i), "123456");
		accounts.push_back(a);
	}

	json accountJsonObj = to_json_array_account(accounts);
	to_json_file(accountJsonObj, accountStore);

	// Demo đọc từ file json
	vector<Account> accounts2 = get_all_accounts_from_json(accountStore);
	for (auto a : accounts2) {
		cout << a.username << ", " << a.password << endl;
	}

	/*auto ids = get_favourite_location_id("favourites.json", "quocpc");
	auto tmp = get_all_favourite_locations_from_json("favourites.json");*/

	// Demo thêm địa điểm yêu thích
	vector<string> tmp;
	tmp.push_back("newplace");
	save_location("favourites.json", "quocpc", tmp);

	// Demo share
	vector<Location> location = get_all_locations_from_json(locationStore);
	string id, user_name;
	string sendtoclient;
	bool check_acc = false;
	for (auto a : accounts2) {
		if (a.username == user_name) {
			check_acc = true;
			for (auto l : location) {
				if (l.id == id) {
					sendtoclient = id;
					//gui den client cua user_name
					send();
				}
			}
		}
	}
	if (check_acc == false) {
		sendtoclient = responseCode.notFoundUsername;   //Khong tim thay user_name
		send();
	}

	//Demo add


	//Communicate with client
	sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	while (1) {
		connSock = accept(listenSock, (sockaddr *)& clientAddr, &clientAddrLen);
		if (connSock == SOCKET_ERROR)
			printf("Error %d: Cannot permit incoming connection.\n", WSAGetLastError());
		else {
			inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));
			clientPort = ntohs(clientAddr.sin_port);
			printf("Accept incoming connection from %s:%d\n", clientIP, clientPort);

			// Start thread
			_beginthreadex(0, 0, userThread, (void *)connSock, 0, 0);
		}
	}

	//Terminate winsock
	WSACleanup();

	return 0;
}

