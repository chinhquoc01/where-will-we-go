#ifdef DELETE
#undef DELETE
#endif

const struct ResponseCode {
	// REGISTER 
	char* successRegister = "100";
	char* errorExistedUsername = "101";

	// LOGIN
	char* successLogin = "110";
	char* errorInvalidAccount = "111";
	char* errorAlreadyLoggedIn = "112";
	char* successGetLocation = "120";
	char* successGetFavorite = "130";
	char* successSave = "140";
	char* errorExistedLocation = "141";
	char* successAdd = "150";
	char* errorInvalidInput = "151";
	char* errorNotExistType = "152";
	char* successDelete = "160";
	char* successShare = "170";
	char* successLogout = "270";
	char* invalidMessage = "999";
	char* errorUnauthorize = "998";
};

const struct Message {
	char* REGISTER = "REGISTER";
	char* LOGIN = "LOGIN";
	char* LOGOUT = "LOGOUT";
	char* GET = "GET";
	char* GETFAVOURITE = "GETFAVOURITE";
	char* SAVE = "SAVE";
	char* ADD = "ADD";
	char* DELETE = "DELETE";
	char* SHARE = "SHARE";
	char* GETSHARELIST = "GETSHARELIST";
	char* ACCEPT = "ACCEPT";
	char* REJECT = "REJECT";
	char* BACKUP = "BACKUP";
	char* RESTORE = "RESTORE";
};