#include "Common.h"
#include "Interface.h"
#include "../Shared/Enum.h"
#include "stdio.h"
#define BUFF_SIZE 2048 
#define SELECT_SIZE 128
#define SEPARATOR_CHAR "$"
#define END_MESS "\r\n"
#pragma comment(lib, "Ws2_32.lib")
const ResponseCode responseCode;
const Message message;

//Nhập vào tài khoản, mật khẩu
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

//Giao diện Đk- Đăng nhập
void register_login(char* buff, char* select_function) {
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
	}
}

//Giao diện chọn loại địa điểm
void IDType(char* select_function) {
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

	printf("Enter number to select IDType: ");
	fflush(stdin);
	gets_s(select_function, SELECT_SIZE);
	
}

//Giao diện chức năng
void function(SOCKET client, char* buff, char* select_function) {
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
					strcpy(buff, message.GET);
					strcat(buff, SEPARATOR_CHAR);
					strcat(buff, select_function);
					strcat(buff, END_MESS);

					send(client, buff, strlen(buff), 0);

					//recv
				} break;
			}
			case 2: {
				system("cls");

				while (1) {
					system("cls");

					printf("See list of favourite location\n");
					IDType(select_function);
					if (strcmp(select_function, "0") == 0) break;
					strcpy(buff, message.GETFAVOURITE);
					strcat(buff, SEPARATOR_CHAR);
					strcat(buff, select_function);
					strcat(buff, END_MESS);

					send(client, buff, strlen(buff), 0);

					//recv
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

				recv(client, buff, BUFF_SIZE, 0);
				getResponseCode(buff);
				Sleep(1000);
			} break;
			case 6: {
				system("cls");

				strcpy(buff, message.RESTORE);
				strcat(buff, END_MESS);

				send(client, buff, strlen(buff), 0);

				recv(client, buff, BUFF_SIZE, 0);

				getResponseCode(buff);
				Sleep(1000);
			} break;
			case 7: {
				system("cls");

				strcpy(buff, message.LOGOUT);
				strcat(buff, END_MESS);

				send(client, buff, strlen(buff), 0);

				recv(client, buff, BUFF_SIZE, 0);
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