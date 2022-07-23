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
SOCKET connSock;

const string accountStore = "accounts.json";

typedef struct {
	string username = "";
	bool isLoggedIn = false;
	string waitingMessage = "";
	vector<string> responses;
} client;

// store account list get from account.txt
vector<Account> accountList;

//const ResponseCode responseCode;

// List function
void getAccountData();
vector<string> split(const string &s, char delim);
vector<string> process(int ret, string buff, client* currentClient);

/* userThread - Thread to receive the user message from client*/
unsigned __stdcall userThread(void *param) {
	char buff[BUFF_SIZE];
	int ret;
	SOCKET connectedSocket = (SOCKET)param;
	
	client currentClient;

	while (1) {
		ret = recv(connectedSocket, buff, BUFF_SIZE, 0);
		if (ret == SOCKET_ERROR) {
			printf("Error %d: Cannot receive data from client[%s:%d]\n", WSAGetLastError(), clientIP, clientPort);
			break;
		}

		else if (strlen(buff) > 0) {
			buff[ret] = '\0';
			string stringBuff(buff);

			process(ret, stringBuff, &currentClient);
			cout << currentClient.responses.size();

			for (int i = 0; i < currentClient.responses.size(); i++) {
				string response = currentClient.responses[i];
				cout << response << endl;
				ret = send(connectedSocket, response.c_str(), strlen(response.c_str()), 0);
				// Send response to client
				if (ret == SOCKET_ERROR) {
					printf("Error %d: Cannot send data to client[%s:%d]\n", WSAGetLastError(), clientIP, clientPort);
					break;
				}
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
	
	/*
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

/*
* @function getAccountData: function to get account data from file account.json and store in account list
*
* @return no return value
*/
void getAccountData() {
	// Get data account from account.json
	accountList.clear();
	accountList = get_all_accounts_from_json(accountStore);
}



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


/*
* @function process: function to process action receive from client
*
* @param ret: return of receive - length of buff
*
* @param buff: string containe receive buffer
*
* @param client: client send to server
*
* @return array string contain list reponses
*/
vector<string> process(int ret, string buff, client* currentClient) {
	if (ret == SOCKET_ERROR) {
		cout << "[-] Error " << WSAGetLastError() << ": Cannot receive data.\n";
		return currentClient->responses;
	}
	else if (ret == 0) {
		printf("[-] Client disconnects.\n");
		return currentClient->responses;
	}

	string temp = currentClient->waitingMessage;
	currentClient->waitingMessage = "";
	vector<string> messages;
	for (int i = 0; i < ret; i++) {
		if (buff[i] == '\r' && buff[i + 1] == '\n') {
			messages.push_back(temp);
			temp = "";
			i++;
		}
		else {
			temp += buff[i];
		}
	}

	// if exist message not have \r\n store this message in waitingMessage
	if (temp != "") {
		currentClient->waitingMessage = temp;
	}

	// process each message
	for (int i = 0; i < messages.size(); i++) {
		if (messages[i] == "") {
			currentClient->responses.push_back("99");
			continue;
		}
		// split message
		vector<string> messageData = split(messages[i], ' ');

		// if message type: USER username
		if (messageData[0] == "USER") {
			if (messageData.size() == 1) {
				currentClient->responses.push_back("99");
			}
			else if (messageData[1] == "") {
				currentClient->responses.push_back("99");
			}
			else {
				//currentClient->responses.push_back(login(messageData[1], currentClient));
				currentClient->responses.push_back("10");
			}
		}
		// if message type: BYE
		else if (messageData[0] == "BYE") {
			//currentClient->responses.push_back(logout(currentClient));
			currentClient->responses.push_back("30");
		}
		// if message does not match any type above => undefine message
		else {
			currentClient->responses.push_back("99");
		}
	}

	return currentClient->responses;
}