#include "Common.h"
#pragma once
class Location
{
public:
	string id;
	string name;
	int type;
	string description;
	string address;
	Location();
	Location(string _id, string _name, int _type, string _description, string _address);
	Location(string _name, int _type, string _description, string _address);
	json to_json_obj();
};

json to_json_array_location(vector<Location> v);
vector<Location> get_all_locations_from_json(string path);

vector<Location> get_location_from_id_list(vector<Location> locations, vector<string> idList);
