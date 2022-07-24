#include "Location.h"

/*
Constructor
*/
Location::Location() {}

/*
Constuctor
*/
Location::Location(string _id, string _name, int _type, string _description, string _address) {
	id = _id;
	name = _name;
	type = _type;
	description = _description;
	address = _address;
}

/*
Constructor
*/
Location::Location(string _name, int _type, string _description, string _address) {
	id = random_string(6);
	name = _name;
	type = _type;
	description = _description;
	address = _address;
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
	jsonObj["address"] = address;
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
		Location l(jsonObj["id"], jsonObj["name"], jsonObj["type"], jsonObj["description"], jsonObj["address"]);
		res.push_back(l);
	}
	return res;
}


/*
Lấy location từ id list
*/
vector<Location> get_location_from_id_list(vector<Location> locations, vector<string> idList) {
	vector<Location> res;
	for (auto id : idList) {
		for (auto location : locations) {
			if (location.id.compare(id) == 0) {
				res.push_back(location);
				break;
			}
		}
	}
	return res;
}

