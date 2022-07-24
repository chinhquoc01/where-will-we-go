#include "Common.h"

/*
Account information
*/
class Account {
public:
	string username;
	string password;
	Account();
	Account(string _username, string _password);
	json to_json_obj();
	static string get_file_path() {
		return ACCOUNTS_PATH;
	}
};

json to_json_array_account(vector<Account> a);
vector<Account> get_all_accounts_from_json(string path);