#include "SharedLocation.h"
#include "LocationService.h"

/*
Get all shared location from file
@params path: path to file
@return vector<SharedLocation>
*/
vector<SharedLocation> get_all_shared_location(string path) {
	auto sharedLocations = get_all_shared_locations_from_json(path);
	return sharedLocations;
}

map<string, vector<string>> get_shared_location_by_username(string path, string username, string locationType) {
	auto sharedLocations = get_all_shared_locations_from_json(path);
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

bool save_shared_location(string path, string sender, string receiver, vector<string> locationIds) {
	// Lấy vector shared location từ file shared
	auto sharedLocations = get_all_shared_location(path);

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

	to_json_file(jsonArray, path);

	return true;
}