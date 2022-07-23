﻿#include "Location.h"
#include "Common.h"

/*
Constructor
*/
Location::Location() {}

/*
Constuctor
*/
Location::Location(string _id, string _name, int _type, string _address, string _description) {
	id = _id;
	name = _name;
	type = _type;
	address = _address;
	description = _description;
}

/*
Constructor
*/
Location::Location(string _name, int _type, string _address, string _description) {
	id = random_string(6);
	name = _name;
	type = _type;
	address = _address;
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
	jsonObj["address"] = address;
	jsonObj["description"] = description;
	return jsonObj;
}

json FavouriteLocation::to_json_obj() {
	auto jsonObj = json::object();
	jsonObj["username"] = username;
	jsonObj["favLocationIdList"] = favLocationIdList;
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

json to_json_array_favourite_location(vector<FavouriteLocation> v) {
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
	for (auto it = j.begin(); it != j.end(); it++)
	{
		json jsonObj(*it);
		Location l(jsonObj["id"], jsonObj["name"], jsonObj["type"], jsonObj["address"], jsonObj["description"]);
		res.push_back(l);
	}
	return res;
}

vector<FavouriteLocation> get_all_favourite_locations_from_json(string path){
	json j = from_json_file(path);
	vector<FavouriteLocation> res;
	for (auto it = j.begin(); it != j.end(); it++) {
		json jsonObj(*it);
		auto favIdList = json::array();
		favIdList = jsonObj["favLocationIdList"];
		vector<string> tmp;
		for (auto e = favIdList.begin(); e != favIdList.end(); e++) {
			json locationId(*e);
			string s = to_string(locationId);
			s.erase(remove(s.begin(), s.end(), '\"'), s.end());
			tmp.push_back(s);
		}
		FavouriteLocation favLocation;
		string username = jsonObj["username"];
		username.erase(remove(username.begin(), username.end(), '\"'), username.end());
		favLocation.username = username;
		favLocation.favLocationIdList = tmp;
		res.push_back(favLocation);
	}
	return res;
}

/*
Lấy danh sách id địa điểm yêu thích từ file theo username
*/
vector<string> get_favourite_location_id(string path, string username) {
	json fav = from_json_file(path);
	vector<string> res;
	for (auto el = fav.begin(); el != fav.end(); el++)
	{
		json favObj(*el);
		string tmp = to_string(favObj["username"]);
		tmp.erase(remove(tmp.begin(), tmp.end(), '\"'), tmp.end());

		if (tmp == username) {
			auto locationList = favObj["favLocationIdList"];
			for (auto e = locationList.begin(); e != locationList.end(); e++) {
				json locationId(*e);
				string s = to_string(locationId);
				s.erase(remove(s.begin(), s.end(), '\"'), s.end());
				res.push_back(s);
			}
			return res;
		}
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

