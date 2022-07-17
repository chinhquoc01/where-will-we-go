
const struct ResponseCode {
	char* successRegister = "100";
	char* errorExistedUsername = "101";
	char* successLogin = "110";
	char* errorInvalidAccount = "111";
	char* successGetLocation = "120";
	char* successGetFavorite = "130";
	char* successSave = "140";
	char* errorExistedLocation = "141";
	char* successAdd = "150";
	char* errorInvalidInput = "151";
	char* errorNotExistType = "152";
	char* successDelete = "160";
	char* successShare = "170";
	char* invalidMessage = "999";
};