#include "Common.h"
#include <stdio.h>

#include <stdlib.h>
#include "../Shared/Enum.h"
#include "conio.h"
#include "../Server/Location.h"
#include "iostream"
#define BUFF_SIZE 2048 
#pragma comment(lib, "Ws2_32.lib")

const ResponseCode responseCode;

void getResponseCode(char* buff) {
	//Register
	if (strcmp(buff, responseCode.successRegister) == 0) {
		printf("Register successfull!\n");
	}
	else if (strcmp(buff, responseCode.errorExistedUsername) == 0) {
		printf("Username doesn't existed!\n");
	}
	//999
	else if (strcmp(buff, responseCode.invalidMessage) == 0) {
		printf("Message isn't determined!\n");
	}
	//Login
	else if (strcmp(buff, responseCode.successLogin) == 0) {
		printf("Login successfull!\n");
	}
	else if (strcmp(buff, responseCode.errorInvalidAccount) == 0){
		printf("Username or password is wrong!\n");
	}
	
	//GET
	else if (strcmp(buff, responseCode.successGetLocation) == 0) {
		printf("Get data successfull!\n");
	}

	//Add
	else if (strcmp(buff, responseCode.successAdd) == 0) {
		printf("Add new location successfull\n");
	}
	else if (strcmp(buff, responseCode.errorInvalidInput) == 0) {
		printf("You haven't input enough infomation!\n");
	}
	else if (strcmp(buff, responseCode.errorNotExistType) == 0) {
		printf("IDType doesn't existed!\n");
	}

	//Save
	else if (strcmp(buff, responseCode.successSave) == 0)
		printf("Sace successfull!");
	else if (strcmp(buff, responseCode.errorExistedLocation) == 0)
		printf("This location has been save before\n");

	//Share 
	else if (strcmp(buff, responseCode.successShare) == 0)
		printf("Share location successfull\n");

	//Backup
	else if (strcmp(buff, responseCode.successBackup) == 0) 
		printf("Backup successfull\n");

	//Restore
	else if (strcmp(buff, responseCode.successRestore) == 0) 
		printf("Restore successfull\n");
	else if (strcmp(buff, responseCode.errorNoBackup) == 0) 
		printf("Account hasn't been backup!\n");

	//Logout
	else if (strcmp(buff, responseCode.successLogout) == 0) 
		printf("Logout successfull\n");
}

vector<string> split(const string &s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

vector<string> recvLocationData(SOCKET client, char* buff) {

	int ret;
	vector<string> locationData;

	ret = recv(client, buff, BUFF_SIZE, 0);
	if (ret == SOCKET_ERROR) {
		if (WSAGetLastError() == WSAETIMEDOUT)
			printf("Time-out!");
		else printf("Error %d: Cannot receive data.", WSAGetLastError());
	}
	else if (strlen(buff) > 0) {
		buff[ret] = 0;
		getResponseCode(buff);
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
				vector<string> messageData = split(response, '$');
				if (messageData.size() < 5) {
					printf("Error when get list location.");
					break;
				}
				for (int j = 0; j < 5; j++)
				{
					locationData.push_back(messageData[j]);
				}
			}
		}
		return locationData;
	}
}