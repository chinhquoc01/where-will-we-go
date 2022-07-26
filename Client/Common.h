#pragma once
#include "vector"
#include "string.h"
#include "Winsock2.h"
using namespace std;
void getResponseCode(char* buff);

vector<string> split(const string &s, char delim);

vector<string> recvLocationData(SOCKET client, char* buff);