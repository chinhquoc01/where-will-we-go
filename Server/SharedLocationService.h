#include "SharedLocation.h"

vector<SharedLocation> get_all_shared_location();

map<string, vector<string>> get_shared_location_by_username(string username, string locationType);

bool save_shared_location(string sender, string receiver, vector<string> locationIds);

bool accept_shared_location(string username, string locationId);

bool reject_shared_location(string username, string locationId);