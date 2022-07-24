#include "FavouriteLocationService.h"

vector<Location> get_favourite_list(string username, string type) {
	auto favLocationIds = get_favourite_location_id(FavouriteLocation::get_file_path(), username);
	auto locations = get_all_locations_from_json(FavouriteLocation::get_file_path());
	auto favLocations = get_location_from_id_list(locations, favLocationIds);
	if (type == "*")
		return favLocations;
	else {
		int typeInt = stoi(type);
		vector<Location> res;
		for (auto fav : favLocations) {
			if (fav.type == typeInt) {
				res.push_back(fav);
			}
		}
		return res;
	}
}

/*
Người dùng tự thêm địa điểm vào danh sách yêu thích
*/
bool add_to_favourite(string username, string locationId, string sender) {
	// Lấy vector favourite location từ file favourite
	auto favouriteLocations = get_all_favourite_locations_from_json(FavouriteLocation::get_file_path());

	bool found = false;
	for (auto & favLocation : favouriteLocations) {
		// Duyệt vector tìm kiếm username
		if (favLocation.username == username) {
			found = true;
			if (favLocation.favLocationIdList.empty()) {
				vector<string> favList{ locationId };
				favLocation.favLocationIdList = favList;
			}
			else {
				// Nếu chưa có trong danh sách yêu thích thì mới thêm
				if (find(favLocation.favLocationIdList.begin(), favLocation.favLocationIdList.end(), locationId) == favLocation.favLocationIdList.end()) {
					favLocation.favLocationIdList.push_back(locationId);
					favLocation.senderList.push_back(sender);
				}

			}
			break;
		}
	}

	// username chưa có trong file favourite
	if (!found) {
		FavouriteLocation newFavLocation;
		vector<string> newFavList{ locationId };
		vector<string> newSenderList{sender};
		newFavLocation.username = username;
		newFavLocation.favLocationIdList = newFavList;
		newFavLocation.senderList = newSenderList;

		favouriteLocations.push_back(newFavLocation);
	}

	auto jsonArray = to_json_array_favourite_location(favouriteLocations);

	to_json_file(jsonArray, FavouriteLocation::get_file_path());

	return true;
}

bool backup_favourite(string username) {
	auto favourites = get_all_favourite_locations_from_json(FavouriteLocation::get_file_path());
	FavouriteLocation favLocation;
	bool check = false;
	for (auto fav : favourites) {
		if (fav.username == username) {
			check = true;
			favLocation = fav;
			break;
		}
	}
	if (!check) return false;

	json jsonObj = favLocation.to_json_obj();
	string backupFile = username + "_backup.json";
	to_json_file(jsonObj, backupFile);
	return true;
}

bool restore_favourite(string username) {
	string backupFile = username + "_backup.json";
	json jsonObj = from_json_file(backupFile);

	FavouriteLocation fav = get_favourite_from_json_object(jsonObj);

	auto oldFavourites = get_all_favourite_locations_from_json(FavouriteLocation::get_file_path());
	vector<FavouriteLocation> newFavourites{ fav };
	for (auto oldFav : oldFavourites) {
		if (oldFav.username != username) {
			newFavourites.push_back(oldFav);
		}
	}
	auto jsonArray = to_json_array_favourite_location(newFavourites);
	to_json_file(jsonArray, FavouriteLocation::get_file_path());
	return true;
}