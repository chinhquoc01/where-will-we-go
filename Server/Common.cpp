#include "Common.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Sinh radom string
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
Trả về json object từ file json
*/
json from_json_file(string path) {
	ifstream i(path);
	json j;
	i >> j;
	return j;
}

/*
Lưu json object về file json
*/
void to_json_file(json j, string path) {
	std::ofstream o(path);
	o << std::setw(4) << j << std::endl;
}


string trim(const string &s){
	auto start = s.begin();
	while (start != s.end() && isspace(*start)) {
		start++;
	}

	auto end = s.end();
	do {
		end--;
	} while (distance(start, end) > 0 && isspace(*end));

	return string(start, end + 1);
}
