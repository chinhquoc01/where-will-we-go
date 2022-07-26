#include "Common.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
* Generate random string
* @param len Length of return string
* @return Random string
*/
string random_string(int len)
{
	string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string newstr;
	time_t t;
	int pos;

	srand((unsigned)time(&t));
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}

/*
* Get json object from json file
* @param path Path to json file
* @return Json object
*/
json from_json_file(string path) {
	ifstream i(path);
	json j;
	i >> j;
	return j;
}

/*
* Save json object as json file
* @param j Json object
* @param path Path to json file output
*/
void to_json_file(json j, string path) {
	std::ofstream o(path);
	o << std::setw(4) << j << std::endl;
}

