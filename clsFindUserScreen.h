#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;

class clsFindUserScreen : protected clsScreen
{
private:

	static void _printUserInfo(clsUser user)
	{
		cout << "\nUser Card:";
		cout << "\n-------------------------------------";
		cout << "\nFirstname   : " << user.firstName;
		cout << "\nLastname    : " << user.lastName;
		cout << "\nFullname    : " << user.fullName();
		cout << "\nEmail       : " << user.email;
		cout << "\nPhone       : " << user.phone;
		cout << "\nUsername    : " << user.userName;
		cout << "\nPassword    : " << user.password;
		cout << "\nPermissions : " << user.permissions;
		cout << "\n-------------------------------------\n";
	}

public:

	static void showFindUserScreen()
	{
		_drawScreenHeader("\tFind User Screen");

		string userName;
		cout << "Please enter a username: ";
		userName = clsInputValidate::readString();

		while (!clsUser::isUserExist(userName))
		{
			cout << "\nUsername is not found, choose another one: ";
			userName = clsInputValidate::readString();
		}

		clsUser user = clsUser::find(userName);

		if (!user.isEmpty())
		{
			cout << "\nUser found :)\n";
		}
		else
		{
			cout << "\nUser was not found!\n";
		}

		_printUserInfo(user);
	}
};

