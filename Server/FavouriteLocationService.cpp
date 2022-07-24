#include "FavouriteLocationService.h"

vector<Location> get_favourite_list(string username) {
	auto favLocationIds = get_favourite_location_id(FavouriteLocation::get_file_path(), username);
	auto locations = get_all_locations_from_json(FavouriteLocation::get_file_path());
	auto favLocations = get_location_from_id_list(locations, favLocationIds);
	return favLocations;
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
