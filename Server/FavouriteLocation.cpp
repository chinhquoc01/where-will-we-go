#include "FavouriteLocation.h"

json FavouriteLocation::to_json_obj() {
	auto jsonObj = json::object();
	jsonObj["username"] = username;
	jsonObj["favLocationIdList"] = favLocationIdList;
	jsonObj["senderList"] = senderList;
	return jsonObj;
}

json to_json_array_favourite_location(vector<FavouriteLocation> v) {
	auto j = json::array();
	for (auto l : v)
	{
		auto jsonObj = l.to_json_obj();
		j.push_back(jsonObj);
	}
	return j;
}

vector<FavouriteLocation> get_all_favourite_locations_from_json(string path) {
	json j = from_json_file(path);
	vector<FavouriteLocation> res;
	for (auto it = j.begin(); it != j.end(); it++) {
		json jsonObj(*it);
		
		auto favLocation = get_favourite_from_json_object(jsonObj);
		res.push_back(favLocation);
	}
	return res;
}

/*
Lấy danh sách id địa điểm yêu thích từ file theo username
*/
vector<string> get_favourite_location_id(string path, string username) {
	json fav = from_json_file(path);
	vector<string> res;
	for (auto el = fav.begin(); el != fav.end(); el++)
	{
		json favObj(*el);
		string tmp = to_string(favObj["username"]);
		tmp.erase(remove(tmp.begin(), tmp.end(), '\"'), tmp.end());

		if (tmp == username) {
			auto locationList = favObj["favLocationIdList"];
			for (auto e = locationList.begin(); e != locationList.end(); e++) {
				json locationId(*e);
				string s = to_string(locationId);
				s.erase(remove(s.begin(), s.end(), '\"'), s.end());
				res.push_back(s);
			}
			return res;
		}
	}
	return res;
}

FavouriteLocation get_favourite_from_json_object(json jsonObj) {
	auto favIdList = json::array();
	favIdList = jsonObj["favLocationIdList"];
	vector<string> tmpFav;
	for (auto e = favIdList.begin(); e != favIdList.end(); e++) {
		json locationId(*e);
		string s = to_string(locationId);
		s.erase(remove(s.begin(), s.end(), '\"'), s.end());
		tmpFav.push_back(s);
	}

	auto senderList = json::array();
	senderList = jsonObj["senderList"];
	vector<string> tmpSender;
	for (auto e = senderList.begin(); e != senderList.end(); e++) {
		json sender(*e);
		string s = to_string(sender);
		s.erase(remove(s.begin(), s.end(), '\"'), s.end());
		tmpSender.push_back(s);
	}

	FavouriteLocation favLocation;
	string username = jsonObj["username"];
	username.erase(remove(username.begin(), username.end(), '\"'), username.end());
	favLocation.username = username;
	favLocation.favLocationIdList = tmpFav;
	favLocation.senderList = tmpSender;

	return favLocation;
}