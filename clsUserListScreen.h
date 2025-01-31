#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsUserListScreen : protected clsScreen
{
private:

	static void _printUserRecordLine(clsUser user)
	{
		cout << "\t| " << setw(15) << left << user.userName;
		cout << "| " << setw(25) << left << user.fullName();
		cout << "| " << setw(12) << left << user.phone;
		cout << "| " << setw(25) << left << user.email;
		cout << "| " << setw(10) << left << user.password;
		cout << "| " << setw(10) << left << user.permissions;
	}

public:

	static void showUserListScreen()
	{
		vector<clsUser> vUsers = clsUser::getUserList();
		string title = "\t User List Screen";
		string subTitle = "\t (" + to_string(vUsers.size()) + ") User(s)";

		/*cout << setw(50) << "Client List (" << vClients.size() << ") Client(s).\n";*/
		_drawScreenHeader(title, subTitle);
		cout << "\t_________________________________________________________________________________________________________________\n\n";
		cout << "\t| " << setw(15) << left << "Username";
		cout << "| " << setw(25) << left << "Full Name";
		cout << "| " << setw(12) << left << "Phone";
		cout << "| " << setw(25) << left << "Email";
		cout << "| " << setw(10) << left << "Password";
		cout << "| " << setw(10) << left << "Permissions";
		cout << "\n\t_________________________________________________________________________________________________________________\n\n";

		if (vUsers.size() == 0)
		{
			cout << "\tNo clients available in the system!\n";
		}
		else
		{
			for (const clsUser& user : vUsers)
			{
				_printUserRecordLine(user);
				cout << "\n";
			}
		}
		cout << "\t_________________________________________________________________________________________________________________\n\n";
	}
};

