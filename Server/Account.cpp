#include "Account.h"
#include "Common.h"
/*
Constructor
*/
Account::Account() {}

/*
Constuctor
*/
Account::Account(string _username, string _password) {
	username = _username;
	password = _password;
}

/*
Method trong class, chuyển account object sang json object
*/
json Account::to_json_obj() {
	auto jsonObj = json::object();
	jsonObj["username"] = username;
	jsonObj["password"] = password;
	return jsonObj;
}

/*
Chuyển từ vector chứa Account sang json object
*/
json to_json_array_account(vector<Account> a) {
	auto j = json::array();
	for (auto l : a)
	{
		auto jsonObj = l.to_json_obj();
		j.push_back(jsonObj);
	}
	return j;
}

/*
Đọc file json, trả về vector chứa Account
*/
vector<Account> get_all_accounts_from_json(string path) {
	json j = from_json_file(path);
	vector<Account> res;
	for (auto it = j.begin(); it != j.end(); ++it)
	{
		json jsonObj(*it);
		Account a(jsonObj["username"], jsonObj["password"]);
		res.push_back(a);
	}
	return res;
}