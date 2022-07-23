#include "stdio.h"
#include "winsock2.h"
#include "ws2tcpip.h"
#include "string"
#include "iostream"

#define BUFF_SIZE 2048

#pragma comment (lib, "Ws2_32.lib")

using namespace std;

#define SERVER_PORT 5500
#define SERVER_ADDR "127.0.0.1"

int main(int argc, char* argv[]) {

	// Initiate Winsock
	WSADATA wsaData;
	WORD vVersion = MAKEWORD(2, 2);
	if (WSAStartup(vVersion, &wsaData)) {
		cout << "Winsock 2.2 is not supported.";
		return 0;
	}
	// Construct socket
	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == INVALID_SOCKET) {
		cout << "Error: " << WSAGetLastError() << ": Cannot create server socket.";
		return 0;
	}

	// Set time-out for receiving
	int timeOutInterval = 10000;
	setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&timeOutInterval), sizeof(int));

	//Specify server address
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);

	// Request to connect server
	if (connect(client, (sockaddr *)&serverAddr, sizeof serverAddr)) {
		cout << "Cannot connect server. Error: " << WSAGetLastError() << "\n";
		return 0;
	}
	cout << "Connected server.\n";

	// Communicate with server
	char buff[BUFF_SIZE];
	int ret, messageLen;

	while (1) {
		cout << "Send to server: ";
		gets_s(buff, BUFF_SIZE);
		messageLen = strlen(buff);

		if (messageLen == 0) break;
		string data(buff);
		data += "\r\n";

		ret = send(client, data.c_str(), strlen(data.c_str()), 0);

		if (ret == SOCKET_ERROR) {
			cout << "Error: " << WSAGetLastError() << "Cannot send data.\n";
		}

		// Receive echo message
		ret = recv(client, buff, BUFF_SIZE, 0);
		if (ret == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAETIMEDOUT) {
				cout << "Time-out.\n";
			}
			else {
				cout << "Error: " << WSAGetLastError() << "Cannot receive data.\n";
			}
		}
		else if (strlen(buff) > 0) {
			buff[ret] = 0;
			cout << "Receive from server: " << buff;
		}
	}

	// Close socket
	closesocket(client);

	// Terminate Winsock
	WSACleanup();
}