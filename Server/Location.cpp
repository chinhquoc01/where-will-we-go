#include "Location.h"
#include "Common.h"

/*
Constructor
*/
Location::Location() {}

/*
Constuctor
*/
Location::Location(string _id, string _name, int _type, string _description) {
	id = _id;
	name = _name;
	type = _type;
	description = _description;
}

/*
Constructor
*/
Location::Location(string _name, int _type, string _description) {
	id = random_string(6);
	name = _name;
	type = _type;
	description = _description;
}

/*
Method của class, chuyển object location thành json object
*/
json Location::to_json_obj() {
	auto jsonObj = json::object();
	jsonObj["id"] = id;
	jsonObj["name"] = name;
	jsonObj["type"] = type;
	jsonObj["description"] = description;
	return jsonObj;
}

/*
Chuyển từ vector location sang dạng json object
*/
json to_json_array_location(vector<Location> v) {
	auto j = json::array();
	for (auto l : v)
	{
		auto jsonObj = l.to_json_obj();
		j.push_back(jsonObj);
	}
	return j;
}


/*
Đọc từ file json, trả về vector chứa location
*/
vector<Location> get_all_locations_from_json(string path) {
	json j = from_json_file(path);
	vector<Location> res;
	for (auto it = j.begin(); it != j.end(); ++it)
	{
		json jsonObj(*it);
		Location l(jsonObj["id"], jsonObj["name"], jsonObj["type"], jsonObj["description"]);
		res.push_back(l);
	}
	return res;
}

