#include "string"
#include "../packages/nlohmann.json.3.10.5/build/native/include/nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;

#define LOCATIONS_PATH "locations.json"
#define ACCOUNTS_PATH "accounts.json"
#define SHARED_LOCATIONS_PATH "sharedLocations.json"
#define FAVOURITE_LOCATIONS_PATH "favouriteLocations.json"

string random_string(int len);


json from_json_file(string path);

void to_json_file(json j, string path);

string trim(const string &s);
