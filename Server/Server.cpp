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
#include "SharedLocationService.h"
#include "../Shared/Enum.h"

#pragma comment (lib,"ws2_32.lib")

#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 2048

int clientPort;
char clientIP[INET_ADDRSTRLEN];
SOCKET sock[4048];
SOCKET connSock;


const ResponseCode responseCode;
const Message sendMessage;

typedef struct {
	string username = "";
	string waitingMessage = "";
	vector<string> responses;
} client;

// store account list get from account.txt
vector<Account> accountList;

// List function
void getAccountData();
vector<string> split(const string &s, char delim);
vector<string> process(int ret, string buff, client* currentClient);
string loginAccount(string username, string password, client* client);
string registerAccount(string username, string password, client* client);
string logoutAccount(client* client);

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

			vector<string> responses = process(ret, stringBuff, &currentClient);

			for (int i = 0; i < responses.size(); i++) {
				string response = responses[i];
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
	accountList = get_all_accounts_from_json(Account::get_file_path());
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
	vector<string> responses;
	if (ret == SOCKET_ERROR) {
		cout << "[-] Error " << WSAGetLastError() << ": Cannot receive data.\n";
		return responses;
	}
	else if (ret == 0) {
		printf("[-] Client disconnects.\n");
		return responses;
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
			responses.push_back("999");
			continue;
		}
		// split message
		vector<string> messageData = split(messages[i], '$');

		// LOGIN
		if (messageData[0] == sendMessage.LOGIN) {
			if (messageData.size() != 3) {
				responses.push_back("999");
			}
			else if (messageData[1] == "" || messageData[2] == "") {
				responses.push_back("999");
			}
			else {
				string response = loginAccount(messageData[1], messageData[2], currentClient);
				responses.push_back(response);
			}
		}
		// REGISTER
		else if (messageData[0] == sendMessage.REGISTER) {
			if (messageData.size() != 3) {
				responses.push_back("999");
			}
			else if (messageData[1] == "" || messageData[2] == "") {
				responses.push_back("999");
			}
			else {
				string response = registerAccount(messageData[1], messageData[2], currentClient);
				responses.push_back(response);
			}
		}
		// LOGOUT
		else if (messageData[0] == sendMessage.LOGOUT) {
			string response = logoutAccount(currentClient);
			responses.push_back(response);
		}
		else {
			responses.push_back("999");
		}
	}

	return responses;
}


string loginAccount(string username, string password, client* client) {
	// Check the account is exist or not, locked or not
	if (username == "") {
		return responseCode.invalidMessage;
	}
	// Check user is logged in or not
	if (client->username != "") {
		return responseCode.errorAlreadyLoggedIn;
	}

	getAccountData();

	for (int i = 0; i < accountList.size(); i++) {
		if (accountList[i].username == username && accountList[i].password == password) {
			client->username = username;
			return responseCode.successLogin;
		}
	}
	return responseCode.errorInvalidAccount;
}


string registerAccount(string username, string password, client* client) {
	// Check the account is exist or not, locked or not
	if (username == "") {
		return responseCode.invalidMessage;
	}
	// Check user is logged in or not
	if (client->username != "") {
		return responseCode.errorAlreadyLoggedIn;
	}

	getAccountData();

	for (int i = 0; i < accountList.size(); i++) {
		if (accountList[i].username == username && accountList[i].password == password) {
			return responseCode.errorExistedUsername;
		}
	}
	Account newAccount(username, password);
	accountList.push_back(newAccount);
	json accountJsonObj = to_json_array_account(accountList);
	to_json_file(accountJsonObj, Account::get_file_path());
	return responseCode.successRegister;
}


string logoutAccount(client* client) {
	if (client->username == "") {
		return responseCode.errorUnauthorize;
	}

	client->username = "";
	return responseCode.successLogout;

}