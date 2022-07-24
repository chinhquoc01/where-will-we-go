#include "AccountService.h"

bool find_account_by_username(string username) {
	auto accounts = get_all_accounts_from_json(Account::get_file_path());
	for (auto account : accounts) {
		if (account.username == username) {
			return true;
		}
	}
	return false;
}