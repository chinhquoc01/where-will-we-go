#include "SharedLocation.h"

vector<SharedLocation> get_all_shared_location(string path);

map<string, vector<string>> get_shared_location_by_username(string path, string username, string locationType);

bool save_shared_location(string path, string sender, string receiver, vector<string> locationIds);

bool accept_shared_location(string path, string username, string locationId);

bool reject_shared_location(string path, string username, string locationId);