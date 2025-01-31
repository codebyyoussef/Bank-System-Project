#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:
	static void _printUserInfo(clsUser user)
	{
		cout << "\nUser Card:";
		cout << "\n-------------------------------------";
		cout << "\nFirstname  : " << user.firstName;
		cout << "\nLastname   : " << user.lastName;
		cout << "\nFullname   : " << user.fullName();
		cout << "\nEmail      : " << user.email;
		cout << "\nPhone      : " << user.phone;
		cout << "\nUsername   : " << user.userName;
		cout << "\nPassword   : " << user.password;
		cout << "\nPermissions : " << user.permissions;
		cout << "\n-------------------------------------\n";
	}

public:
	static void showDeleteUserScreen()
	{
		_drawScreenHeader("\tDelete User Screen");

		string userName;
		cout << "Please enter a username: ";
		userName = clsInputValidate::readString();

		while (!clsUser::isUserExist(userName))
		{
			cout << "\nUser is not found, choose another one: ";
			userName = clsInputValidate::readString();
		}

		clsUser user = clsUser::find(userName);

		_printUserInfo(user);

		char deleteUser = 'n';
		cout << "Are you sure you want to delete this user? y/n? ";
		cin >> deleteUser;

		if (deleteUser == 'y' || deleteUser == 'Y')
		{
			if (user.Delete())
			{
				cout << "\nUser deleted successfully :)\n";
				_printUserInfo(user);
			}
			else
			{
				cout << "\nError User Was not Deleted\n";
			}
		}

	}
};

