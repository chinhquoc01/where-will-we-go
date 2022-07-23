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

class FavouriteLocation {
public:
	string username;
	vector<string> favLocationIdList;
	json to_json_obj();
};


json to_json_array_location(vector<Location> v);
vector<string> get_favourite_location_id(string path, string username);
vector<Location> get_location_from_id_list(vector<Location> locations, vector<string> idList);

vector<Location> get_all_locations_from_json(string path);
json to_json_array_favourite_location(vector<FavouriteLocation> favLocations);
vector<FavouriteLocation> get_all_favourite_locations_from_json(string path);