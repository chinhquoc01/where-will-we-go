#pragma once
#include "LocationService.h"

vector<Location> get_all_location() {
	auto locations = get_all_locations_from_json(Location::get_file_path());
	return locations;
}


vector<Location> get_locations_by_type(string type) {
	auto locations = get_all_locations_from_json(Location::get_file_path());
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

Location get_location_by_id(string id) {
	auto locations = get_all_location();
	for (auto l : locations) {
		if (l.id == id) {
			return l;
		}
	}
	throw;
}