#pragma once
#include "vector"
#include "string.h"
#include "Winsock2.h"
using namespace std;
void getResponseCode(char* buff);

/*
* @function split: split string by delim character
*
* @param string: string want to split
*
* @param delim: character to split
*
* @return: array string after split
*/
vector<string> split(const string &s, char delim);

vector<string> recvLocationData(SOCKET client, char* buff);