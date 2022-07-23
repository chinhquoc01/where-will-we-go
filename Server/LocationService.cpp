#include "LocationService.h"

vector<Location> get_all_location(string path) {
	auto locations = get_all_locations_from_json(path);
	return locations;
}





vector<Location> get_locations_by_type(string type, string path = "locations.json") {
	auto locations = get_all_locations_from_json(path);
	if (type == "*") {
		return locations;
	}
	int typeInt = stoi(type);
	vector<Location> res;
	for (auto location : locations) {
		if (location.type == typeInt) {
			res.push_back(location);
		}
	}
	return res;
}