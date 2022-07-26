#include "Location.h"

/*
Constructor
*/
Location::Location() {}

/*
Constuctor
*/
Location::Location(string _id, string _name, int _type, string _description, string _address)
{
	id = _id;
	name = _name;
	type = _type;
	description = _description;
	address = _address;
}

/*
Constructor
*/
Location::Location(string _name, int _type, string _description, string _address)
{
	id = random_string(6);
	name = _name;
	type = _type;
	description = _description;
	address = _address;
}

/*
* Method get json object
*/
json Location::to_json_obj()
{
	auto jsonObj = json::object();
	jsonObj["id"] = id;
	jsonObj["name"] = name;
	jsonObj["type"] = type;
	jsonObj["description"] = description;
	jsonObj["address"] = address;
	return jsonObj;
}

/*
* Get json object from vector of location
* @param v vector of locations
* @return json object
*/
json to_json_array_location(vector<Location> v)
{
	auto j = json::array();
	for (auto l : v)
	{
		auto jsonObj = l.to_json_obj();
		j.push_back(jsonObj);
	}
	return j;
}

/*
* Read file json then return vector of location
* @param path Path to json file
* @return vector of location
*/
vector<Location> get_all_locations_from_json(string path)
{
	json j = from_json_file(path);
	vector<Location> res;
	for (auto it = j.begin(); it != j.end(); it++)
	{
		json jsonObj(*it);
		Location l(jsonObj["id"], jsonObj["name"], jsonObj["type"], jsonObj["description"], jsonObj["address"]);
		res.push_back(l);
	}
	return res;
}

/*
* Get location object from id
* @param locations Vector of locations
* @param idList Vector of location id
* @return Vector of location from @idList
*/
vector<Location> get_location_from_id_list(vector<Location> locations, vector<string> idList)
{
	vector<Location> res;
	for (auto id : idList)
	{
		for (auto location : locations)
		{
			if (location.id.compare(id) == 0)
			{
				res.push_back(location);
				break;
			}
		}
	}
	return res;
}
