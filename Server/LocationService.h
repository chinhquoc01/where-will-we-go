#include "Location.h"

vector<Location> get_all_location(string path);

vector<Location> get_favourite_list(string path, string username);

bool save_location(string path, string username, vector<string> locationIds);

vector<Location> get_locations_by_type(string type, string path = "locations.json");