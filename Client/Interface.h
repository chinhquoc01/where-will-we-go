#pragma once
#include "Winsock2.h"
#pragma comment(lib, "Ws2_32.lib")


void input(char* buff, char* select_function);

void UI_register_login(char* buff, char* select_function);

void clientProcess(SOCKET client, char* buff, char* select_function, bool haveNoti);

