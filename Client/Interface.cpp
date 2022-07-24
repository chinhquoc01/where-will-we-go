#include "Common.h"
#include "Interface.h"
#include "../Shared/Enum.h"
#include "stdio.h"
#include "iostream"
#include "ctype.h"
#include <string>

#define BUFF_SIZE 2048 
#define SELECT_SIZE 128
#define SEPARATOR_CHAR "$"
#define END_MESS "\r\n"
#pragma comment(lib, "Ws2_32.lib")
const ResponseCode responseCode;
const Message message;

using namespace std;

//Input username, password
void input(char* buff, char* select_function) {
	char temp[BUFF_SIZE];

	system("cls");

	if (strcmp(select_function, "1") == 0) {
		strcpy(buff, message.REGISTER);
		strcat(buff, SEPARATOR_CHAR);
		printf("REGISTER\n");
	}

	else if (strcmp(select_function, "2") == 0) {
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

//Register-Login nterface
void UI_register_login(char* buff, char* select_function) {
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

	printf("Enter number to select function: ");
	fflush(stdin);
	gets_s(select_function, SELECT_SIZE);

	if (strcmp(select_function, "1") == 0 || strcmp(select_function, "2") == 0) {
		input(buff, select_function);
	}

	else if (strcmp(select_function, "3") == 0) {

	}
	else {
		printf("Function doesn't exist\n");
		strcpy(select_function, "0");
		Sleep(1000);
	}
}

//Get list of location
void getLocation(vector<string> locationData, char* select_function) {
	system("cls");

	int nameSizeMax = 0, addressSizeMax = 0;
	if (locationData.size() < 5) {
		return;
	}
	else {
		for (int i = 0; i < locationData.size(); i += 5) {
			if (nameSizeMax < locationData[i+1].size()) nameSizeMax = locationData[i+1].size();
			if (addressSizeMax < locationData[i+3].size()) addressSizeMax = locationData[i+3].size();
		}

	}
	if (strcmp(select_function, "*") == 0) cout << "List of all location" << endl;
	else {
		int key = atoi(select_function);
		switch (key) {
		case 1: cout << "List of restaurant location" << endl; break;
		case 2: cout << "List of coffee location" << endl; break;
		case 3: cout << "List of cinema location" << endl; break;
		case 4: cout << "List of fashion shop location" << endl; break;
		}
	}
	
	printf("(IDtype) Restaurant : 1, Coffee: 2, Cinema: 3, Fashion shop: 4\n");
	cout << "NUMBER      ID       Name";
	for (int i = 0; i < nameSizeMax; i++) printf(" ");
	cout << "IDType";
	for (int i = 0; i < 4; i++) printf(" ");
	cout << "Address";
	for (int i = 0; i < (addressSizeMax - 2); i++) printf(" ");
	cout << "Description" << endl;
	int count = 1;
	for (int i = 0; i < locationData.size(); i++) {
		//printf number
		cout << "  " << count;
		count++;
		//printf id
		cout << "       " + locationData[i];
		i++;
		//printf name
		cout << "     " + locationData[i];
		i++;
		//printf idtype
		for (int i = 0; i < nameSizeMax; i++) cout << " ";
		cout << "  " + locationData[i];
		i++;
		//printf address
		for (int i = 0; i < addressSizeMax; i++) cout << " ";
		cout << " " + locationData[i + 1];
		i++;
		//printf description
		cout << "     " + locationData[i - 1] << endl;
	}
}

//Select IDType interface
void IDType(char* select_function) {
	printf("---------------------------------------------\n");
	printf("| IDType|               TYPE                |\n");
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

	printf("Enter number to select IDType: ");
	fflush(stdin);
	gets_s(select_function, SELECT_SIZE);
	
}

//fuction interface
void clientProcess(SOCKET client, char* buff, char* select_function) {
	system("cls");

	while (1) {
		if (strcmp(select_function, "7") == 0) break;

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

		printf("Enter number to select function: ");
		fflush(stdin);
		gets_s(select_function, SELECT_SIZE);

		int key = atoi(select_function);
		switch (key) {
			case 1: {
				system("cls");

				while (1) {
					system("cls");
					printf("See list of location\n");
					IDType(select_function);

					if (strcmp(select_function, "0") == 0) break;
					else if (strcmp(select_function, "1") != 0 && strcmp(select_function, "2") != 0
						&& strcmp(select_function, "3") != 0 && strcmp(select_function, "4") != 0
						&& strcmp(select_function, "*") != 0) {
						printf("IDType doesn't exist\n");
						Sleep(1000); continue;
					}

					strcpy(buff, message.GET);
					strcat(buff, SEPARATOR_CHAR);
					strcat(buff, select_function);
					strcat(buff, END_MESS);

					send(client, buff, strlen(buff), 0);

					//recv
					vector<string> locationData = recvLocationData(client, buff);
					getLocation(locationData, select_function);

					char tmp[SELECT_SIZE];
					printf("0. Comeback\n");
					printf("1. Enter number of location: ");
					fflush(stdin);
					gets_s(tmp);
					printf("---------------------------------------\n");
					if (strcmp(tmp, "0") == 0) continue;
					else if (isdigit(*tmp) == 0) printf("Location doesn't existed!\n");
					else {
						if (atoi(tmp)> locationData.size()/5 || atoi(tmp) < 0) printf("Location doesn't existed!\n");
						else {
							char tmp1[SELECT_SIZE];
							printf("1. Save\n");
							printf("2. Shared\n");
							printf("0. Comeback\n");
							printf("Enter number to select function: ");
							fflush(stdin);
							gets_s(tmp1);
							
							
							if (strcmp(tmp1, "1") == 0) {
								strcpy(buff, message.SAVE);
								strcat(buff, SEPARATOR_CHAR);
								
								strcat(buff, locationData[(atoi(tmp) - 1) * 5].c_str());
								strcat(buff, END_MESS);
								cout << string(buff) << endl;
								printf("---------------------------------------\n");
								send(client, buff, strlen(buff), 0);

								int ret = recv(client, buff, BUFF_SIZE, 0);
								buff[ret] = 0;
								getResponseCode(buff);
							}
							else if (strcmp(tmp1, "2") == 0) {
								strcpy(buff, message.SHARE);
								strcat(buff, SEPARATOR_CHAR);
								strcat(buff, locationData[(atoi(tmp)-1) * 5].c_str());
								strcat(buff, SEPARATOR_CHAR);
								printf("Share to: ");
								fflush(stdin);
								gets_s(tmp);
								strcat(buff, tmp);
								strcat(buff, END_MESS);

								send(client, buff, strlen(buff), 0);

								int ret = recv(client, buff, BUFF_SIZE, 0);
								buff[ret] = 0;
								getResponseCode(buff);

							}
							else if (strcmp(tmp1, "0") == 0) {
								continue;
							}
							else {
								printf("Function doesn't exist\n");
								strcpy(select_function, "0");
							}

							Sleep(1000);
						}
					}
				} break;
			}
			case 2: {
				system("cls");

				while (1) {
					system("cls");

					printf("See list of favourite location\n");
					IDType(select_function);
					
					if (strcmp(select_function, "0") == 0) break;
					else if (strcmp(select_function, "1") != 0 && strcmp(select_function, "2") != 0
						&& strcmp(select_function, "3") != 0 && strcmp(select_function, "4") != 0
						&& strcmp(select_function, "*") != 0) {
						printf("IDType doesn't exist\n");
						Sleep(1000); continue;
					}

					strcpy(buff, message.GETFAVOURITE);
					strcat(buff, SEPARATOR_CHAR);
					strcat(buff, select_function);
					strcat(buff, END_MESS);

					send(client, buff, strlen(buff), 0);

					//recv
					vector<string> locationData = recvLocationData(client, buff);
					getLocation(locationData, select_function);
					
				} break;
			}
			case 3: {
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
				strcat(buff, SEPARATOR_CHAR);

				printf("IDType: ");
				fflush(stdin);
				gets_s(inp);
				strcat(buff, inp);
				strcat(buff, SEPARATOR_CHAR);

				printf("Address: ");
				fflush(stdin);
				gets_s(inp);
				strcat(buff, inp);
				strcat(buff, SEPARATOR_CHAR);

				printf("Description: ");
				fflush(stdin);
				gets_s(inp);
				strcat(buff, inp);
				strcat(buff, END_MESS);

				send(client, buff, strlen(buff), 0);
				cout << string(buff) << endl;

				int ret = recv(client, buff, BUFF_SIZE, 0);
				buff[ret] = 0;
				cout << string(buff) << endl;

				getResponseCode(buff);
				Sleep(1000);
			} break;
			case 4: {
				system("cls");

				strcpy(buff, message.GETSHARELIST);
				strcat(buff, END_MESS);

				send(client, buff, strlen(buff), 0);

				//recv
			} break;
			case 5: {
				system("cls");

				strcpy(buff, message.BACKUP);
				strcat(buff, END_MESS);

				send(client, buff, strlen(buff), 0);
				cout << string(buff) << endl;

				int ret = recv(client, buff, BUFF_SIZE, 0);
				buff[ret] = 0;
				cout << string(buff) << endl;
				getResponseCode(buff);
				Sleep(10000);
			} break;
			case 6: {
				system("cls");

				strcpy(buff, message.RESTORE);
				strcat(buff, END_MESS);

				send(client, buff, strlen(buff), 0);

				int ret = recv(client, buff, BUFF_SIZE, 0);
				buff[ret] = 0;

				getResponseCode(buff);
				Sleep(1000);
			} break;
			case 7: {
				system("cls");

				strcpy(buff, message.LOGOUT);
				strcat(buff, END_MESS);

				send(client, buff, strlen(buff), 0);

				int ret = recv(client, buff, BUFF_SIZE, 0);
				buff[ret] = 0;

				getResponseCode(buff);
				Sleep(1000);
			} break;
			default: {
				printf("Function doesn't exist\n");
				Sleep(1000);
			}	
		}
	}
}