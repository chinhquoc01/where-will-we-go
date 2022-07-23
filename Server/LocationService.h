#pragma once
#include "Location.h"

vector<Location> get_all_location(string path);

vector<Location> get_locations_by_type(string type, string path = "locations.json");