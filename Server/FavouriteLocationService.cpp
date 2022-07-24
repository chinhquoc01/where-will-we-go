#include "FavouriteLocationService.h"

vector<Location> get_favourite_list(string path, string username) {
	auto favLocationIds = get_favourite_location_id(path, username);
	auto locations = get_all_locations_from_json(path);
	auto favLocations = get_location_from_id_list(locations, favLocationIds);
	return favLocations;
}


bool save_location(string path, string username, vector<string> locationIds) {
	// Lấy vector favourite location từ file favourite
	auto favouriteLocations = get_all_favourite_locations_from_json(path);

	bool found = false;
	for (auto & favLocation : favouriteLocations) {
		// Duyệt vector tìm kiếm username
		if (favLocation.username == username) {
			found = true;
			if (favLocation.favLocationIdList.empty()) {
				favLocation.favLocationIdList = locationIds;
			}
			else {
				for (auto id : locationIds) {
					// Nếu chưa có trong danh sách yêu thích thì mới thêm
					if (find(favLocation.favLocationIdList.begin(), favLocation.favLocationIdList.end(), id) == favLocation.favLocationIdList.end()) {
						favLocation.favLocationIdList.push_back(id);
					}
				}

			}
			break;
		}
	}

	// username chưa có trong file favourite
	if (!found) {
		FavouriteLocation newFavLocation;
		newFavLocation.username = username;
		newFavLocation.favLocationIdList = locationIds;
		favouriteLocations.push_back(newFavLocation);
	}

	auto jsonArray = to_json_array_favourite_location(favouriteLocations);

	to_json_file(jsonArray, path);

	return true;
}