#include "Common.h"

class SharedLocation {
public:
	string sender;
	string receiver;
	vector<string> sharedList;
	json to_json_obj();
	static string get_file_path() {
		return SHARED_LOCATIONS_PATH;
	};
};

json to_json_array_shared_location(vector<SharedLocation> v);

vector<SharedLocation> get_all_shared_locations_from_json(string path);