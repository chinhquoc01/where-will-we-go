#include "Location.h"
#include "FavouriteLocation.h"

vector<Location> get_favourite_list(string username, string type);

bool add_to_favourite(string username, string locationId, string sender = "");

bool backup_favourite(string username);

bool restore_favourite(string username);