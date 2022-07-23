#include "Common.h"
#include <fstream>

/*
Sinh radom string
*/
string random_string(int len)
{
	string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string newstr;
	int pos;
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

//json to_json_array_from_vector(vector<BaseClass*> v) {
//	auto j = json::array();
//	for (auto l : v)
//	{
//		auto jsonObj = (*l).to_json_obj();
//		j.push_back(jsonObj);
//	}
//	return j;
//}
