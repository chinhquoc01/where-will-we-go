#include "Location.h"
#include "FavouriteLocation.h"

vector<Location> get_favourite_list(string path, string username);

bool add_to_favourite(string path, string username, string locationId, string sender = "");
