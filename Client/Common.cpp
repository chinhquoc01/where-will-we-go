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

/*
* @function getResponseCode: Printf message after client received response code
*
* @param buff: response code client received
*/
void getResponseCode(char* buff) {
	// Register
	if (strcmp(buff, responseCode.successRegister) == 0) {
		printf("Register successfull!\n");
	}
	else if (strcmp(buff, responseCode.errorExistedUsername) == 0) {
		printf("Username exist!\n");
	}
	
	// Login
	else if (strcmp(buff, responseCode.successLogin) == 0) {
		printf("Login successfull!\n");
	}
	else if (strcmp(buff, responseCode.errorInvalidAccount) == 0){
		printf("Username or password is wrong!\n");
	}
	else if (strcmp(buff, responseCode.errorAlreadyLoggedIn) == 0) {
		printf("Already Logged in!\n");
	}
	
	// GET
	else if (strcmp(buff, responseCode.successGetLocation) == 0) {
		printf("Get data successfull!\n");
	}

	// GETFOURITE
	else if (strcmp(buff, responseCode.successGetFavorite) == 0) {
		printf("Get data successfull!\n");
	}

	// Add
	else if (strcmp(buff, responseCode.successAdd) == 0) 
		printf("Add new location successfull\n");
	else if (strcmp(buff, responseCode.errorInvalidInput) == 0) {
		printf("Invalid input!\n");
	}
	else if (strcmp(buff, responseCode.errorNotExistType) == 0) {
		printf("IDType doesn't exist!\n");
	}

	// Delete
	else if (strcmp(buff, responseCode.successDelete) == 0) {
		printf("Delete successfull!\n");
	}
	else if (strcmp(buff, responseCode.errorDelete) == 0) {
		printf("Error delete!\n");
	}

	// Save
	else if (strcmp(buff, responseCode.successSave) == 0)
		printf("Save successfull!\n");
	else if (strcmp(buff, responseCode.errorExistedLocation) == 0)
		printf("This location has been save before\n");

	// Share 
	else if (strcmp(buff, responseCode.successShare) == 0)
		printf("Share location successfull\n");
	else if (strcmp(buff, responseCode.notFoundUsername) == 0)
		printf("Username doesn't exist!\n");
	else if (strcmp(buff, responseCode.errorSelfShare) == 0)
		printf("Can not share to your account!\n");
	// Getshareslist
	else if (strcmp(buff, responseCode.successGetSharedList) == 0)
		printf("Get data successfull!\n");
	// Backup
	else if (strcmp(buff, responseCode.successBackup) == 0) 
		printf("Backup successfull\n");
	else if (strcmp(buff, responseCode.errorBackup) == 0)
		printf("Error backup!\n");

	// Restore
	else if (strcmp(buff, responseCode.successRestore) == 0) 
		printf("Restore successfull\n");
	else if (strcmp(buff, responseCode.errorNoBackup) == 0) 
		printf("Account hasn't been backup!\n");

	// Accept
	else if (strcmp(buff, responseCode.successAccept) == 0)
		printf("Accept successfull!\n");
	else if (strcmp(buff, responseCode.errorAccept) == 0)
		printf("Error accept!\n");
	// Reject
	else if (strcmp(buff, responseCode.successReject) == 0)
		printf("Reject successfull!\n");
	else if (strcmp(buff, responseCode.errorReject) == 0)
		printf("Error reject!\n");
	// Logout
	else if (strcmp(buff, responseCode.successLogout) == 0) 
		printf("Logout successfull!\n");

	// Unauthorize
	else if (strcmp(buff, responseCode.errorUnauthorize) == 0)
		printf("Unauthorize!\n");
	// 999
	else {
		printf("Message isn't determined!\n");
	}
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
* @function recvLocationData: received location data
*
* @param buff: response code and data client received
*
* @param client: socket of client
* 
* @return: 
*/
vector<string> recvLocationData(SOCKET client, char* buff) {

	int ret;
	vector<string> locationData;

	//received response code
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
	if (responseCodeGetLocation == responseCode.successGetLocation || responseCodeGetLocation == responseCode.successGetFavorite
		|| responseCodeGetLocation == responseCode.successGetSharedList) {
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
				if(strcmp(buff, "nodata") == 0) return vector<string>{""};
				string response(buff);
				
				vector<string> messageData = split(response, '$');
				if (responseCodeGetLocation == responseCode.successGetSharedList) {
					if (messageData.size() < 6) {
						printf("List location is empty.\n");
					}
					for (int j = 0; j < 6; j++)
					{
						locationData.push_back(messageData[j]);
					}
				}
				else {
					if (messageData.size() < 5) {
						printf("List location is empty.\n");
					}
					for (int j = 0; j < 5; j++)
					{
						locationData.push_back(messageData[j]);
					}
				}
				
			}
		}
		return locationData;
	}
}