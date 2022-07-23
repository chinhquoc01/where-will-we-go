#include "Common.h"


class Location {
public:
	string id;
	string name;
	int type;
	string address;
	string description;
	Location();
	Location(string _id, string _name, int _type, string _address, string _description);
	Location(string _name, int _type, string _address, string _description);
	json to_json_obj();
};


json to_json_array_location(vector<Location> v);
vector<Location> get_all_locations_from_json(string path);
vector<string> get_favourite_location_id(string path, string username);
vector<Location> get_location_from_id_list(vector<Location> locations, vector<string> idList);