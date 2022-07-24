#include "SharedLocation.h"
#include "LocationService.h"
#include "FavouriteLocationService.h"

/*
Get all shared location from file
@params path: path to file
@return vector<SharedLocation>
*/
vector<SharedLocation> get_all_shared_location() {
	auto sharedLocations = get_all_shared_locations_from_json(SharedLocation::get_file_path());
	return sharedLocations;
}

map<string, vector<string>> get_shared_location_by_username(string username, string locationType) {
	auto sharedLocations = get_all_shared_locations_from_json(SharedLocation::get_file_path());
	map<string, vector<string>> mapShared;
	for (auto sharedLocation : sharedLocations) {
		if (sharedLocation.receiver == username) {
			for (auto idLocation : sharedLocation.sharedList) {
				if (mapShared.find(idLocation) == mapShared.end()) {
					// not found
					vector<string> vect{ sharedLocation.sender };
					mapShared[idLocation] = vect;
				}
				else {
					// found
					mapShared[idLocation].push_back(sharedLocation.sender);
				}
			}
		}
	}
	if (locationType == "*") {
		return mapShared;
	}
	auto locationByType = get_locations_by_type(locationType);
	map<string, vector<string>> res;
	for (auto tmp : locationByType) {
		auto found = mapShared.find(tmp.id);
		if (found != mapShared.end()) {
			res[found->first] = found->second;
		}
	}
	return res;
}

bool save_shared_location(string sender, string receiver, vector<string> locationIds) {
	// Lấy vector shared location từ file shared
	auto sharedLocations = get_all_shared_location();

	bool found = false;
	for (auto & sharedLocation : sharedLocations) {
		// Duyệt vector tìm kiếm username
		if (sharedLocation.sender == sender && sharedLocation.receiver == receiver) {
			found = true;
			if (sharedLocation.sharedList.empty()) {
				sharedLocation.sharedList = locationIds;
			}
			else {
				for (auto id : locationIds) {
					// Nếu chưa có trong danh sách yêu thích thì mới thêm
					if (find(sharedLocation.sharedList.begin(), sharedLocation.sharedList.end(), id) == sharedLocation.sharedList.end()) {
						sharedLocation.sharedList.push_back(id);
					}
				}
			}
			break;
		}
	}

	// username chưa có trong file favourite
	if (!found) {
		SharedLocation newSharedLocation;
		newSharedLocation.sender = sender;
		newSharedLocation.receiver = receiver;
		newSharedLocation.sharedList = locationIds;
		sharedLocations.push_back(newSharedLocation);
	}

	auto jsonArray = to_json_array_shared_location(sharedLocations);

	to_json_file(jsonArray, SharedLocation::get_file_path());

	return true;
}

bool accept_shared_location(string username, string locationId) {
	auto allSharedLocation = get_all_shared_location();
	string sender;
	bool accept = false;
	// Xoá từ kho shared
	for (auto & shared : allSharedLocation) {
		auto found = find(shared.sharedList.begin(), shared.sharedList.end(), locationId);
		if (shared.receiver == username && found != shared.sharedList.end()) {
			accept = true;
			shared.sharedList.erase(found);
			if (sender.empty()) {
				sender = shared.sender;
			}
		}
	}
	json sharedArrayJson = to_json_array_shared_location(allSharedLocation);
	to_json_file(sharedArrayJson, SharedLocation::get_file_path());

	if (accept) {
		// Thêm vào favourite
		add_to_favourite(username, locationId, sender);
	}

	return true;
}

bool reject_shared_location(string username, string locationId) {
	auto allSharedLocation = get_all_shared_location();
	string sender;

	// Xoá từ kho shared
	for (auto & shared : allSharedLocation) {
		auto found = find(shared.sharedList.begin(), shared.sharedList.end(), locationId);
		if (shared.receiver == username && found != shared.sharedList.end()) {
			shared.sharedList.erase(found);
			if (sender.empty()) {
				sender = shared.sender;
			}
		}
	}
	json sharedArrayJson = to_json_array_shared_location(allSharedLocation);
	to_json_file(sharedArrayJson, "sharedLocations.json");
	return true;
}