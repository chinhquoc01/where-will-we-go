#include "Common.h"

class FavouriteLocation {
public:
	string username;
	vector<string> favLocationIdList;
	json to_json_obj();
};

json to_json_array_favourite_location(vector<FavouriteLocation> favLocations);
vector<FavouriteLocation> get_all_favourite_locations_from_json(string path);
vector<string> get_favourite_location_id(string path, string username);