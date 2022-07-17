#include "string"
#include "nlohmann\json.hpp"
using namespace std;
using json = nlohmann::json;

/*
Hàm tạo random string
*/
string random_string(int len);

/*
Đọc json object từ file json
*/
json from_json_file(string path);

void to_json_file(json j, string path);
