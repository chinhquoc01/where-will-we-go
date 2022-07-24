#include "Common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Shared/Enum.h"

const ResponseCode responseCode;

void getResponseCode(char* buff) {
	//Register
	if (strcmp(buff, responseCode.successRegister) == 0) {
		printf("Register successfull!\n");
	}
	else if (strcmp(buff, responseCode.errorExistedUsername) == 0) {
		printf("Username doesn't existed!\n");
	}
	//999
	else if (strcmp(buff, responseCode.invalidMessage) == 0) {
		printf("Message isn't determined!\n");
	}
	//Login
	else if (strcmp(buff, responseCode.successLogin) == 0) {
		printf("Login successfull!\n");
	}
	else if (strcmp(buff, responseCode.errorInvalidAccount) == 0){
		printf("Username or password is wrong!\n");
	}
	

	//Add
	else if (strcmp(buff, responseCode.successAdd) == 0) {
		printf("Add new location successfull\n");
	}
	else if (strcmp(buff, responseCode.errorInvalidInput) == 0) {
		printf("You haven't input enough infomation!\n");
	}
	else if (strcmp(buff, responseCode.errorNotExistType) == 0) {
		printf("IDType doesn't existed!\n");
	}

	//Backup
	else if (strcmp(buff, responseCode.successBackup) == 0) {
		printf("Backup successfull\n");
	}

	//Restore
	else if (strcmp(buff, responseCode.successRestore) == 0) {
		printf("Restore successfull\n");
	}
	else if (strcmp(buff, responseCode.errorNoBackup) == 0) {
		printf("Account hasn't been backup!\n");
	}

	//Logout
	else if (strcmp(buff, responseCode.successLogout) == 0) {
		printf("Logout successfull\n");
	}
}