#include "SharedLocation.h"

json SharedLocation::to_json_obj() {
	auto jsonObj = json::object();
	jsonObj["sender"] = sender;
	jsonObj["receiver"] = receiver;
	jsonObj["sharedList"] = sharedList;
	return jsonObj;
}

json to_json_array_shared_location(vector<SharedLocation> v) {
	auto j = json::array();
	for (auto l : v)
	{
		auto jsonObj = l.to_json_obj();
		j.push_back(jsonObj);
	}
	return j;
}

vector<SharedLocation> get_all_shared_locations_from_json(string path) {
	json j = from_json_file(path);
	vector<SharedLocation> res;
	for (auto it = j.begin(); it != j.end(); it++) {
		json jsonObj(*it);
		auto sharedIds = json::array();
		sharedIds = jsonObj["sharedList"];
		vector<string> tmp;
		for (auto e = sharedIds.begin(); e != sharedIds.end(); e++) {
			json locationId(*e);
			string s = to_string(locationId);
			s.erase(remove(s.begin(), s.end(), '\"'), s.end());
			tmp.push_back(s);
		}
		SharedLocation sharedLocation;
		string sender = jsonObj["sender"];
		sender.erase(remove(sender.begin(), sender.end(), '\"'), sender.end());
		sharedLocation.sender = sender;

		string receiver = jsonObj["receiver"];
		receiver.erase(remove(receiver.begin(), receiver.end(), '\"'), receiver.end());
		sharedLocation.receiver = receiver;

		sharedLocation.sharedList = tmp;
		res.push_back(sharedLocation);
	}
	return res;
}