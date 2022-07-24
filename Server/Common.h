#include "string"
#include "../packages/nlohmann.json.3.10.5/build/native/include/nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;

//class BaseClass {
//public:
//	virtual json to_json_obj();
//};

/*
Hàm tạo random string
*/
string random_string(int len);

/*
Đọc json object từ file json
*/
json from_json_file(string path);

void to_json_file(json j, string path);

//json to_json_array_from_vector(vector<BaseClass> v);