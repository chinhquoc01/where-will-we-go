#pragma once
#include "Winsock2.h"
#pragma comment(lib, "Ws2_32.lib")

//input username ,password
void input(char* buff, char* select_function);

//Giao dien dang ky dang nhap
void register_login(char* buff, char* select_function);

//Giao dien cac chuc nang
void function(SOCKET client, char* buff, char* select_function);
