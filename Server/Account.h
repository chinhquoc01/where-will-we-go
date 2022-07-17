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
};

json to_json_array_account(vector<Account> a);
vector<Account> get_all_accounts_from_json(string path);