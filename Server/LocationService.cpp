#pragma once
#include "LocationService.h"

/*
* Get all location from data storage
* @return Vector contains list of all locations
*/
vector<Location> get_all_location() {
	auto locations = get_all_locations_from_json(Location::get_file_path());
	return locations;
}

/*
* Get all locations from data storage by type
* @param type Type of location
* @return Vector contains list of location by type
*/
vector<Location> get_locations_by_type(string type) {
	try
	{

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
	catch (const std::exception&)
	{
		vector<Location> ret;
		return ret;
	}
}

/*
* Get location by id
* @param id Id of location
* @return Location object
*/
Location get_location_by_id(string id) {
	auto locations = get_all_location();
	for (auto l : locations) {
		if (l.id == id) {
			return l;
		}
	}
	throw;
}