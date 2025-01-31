#pragma once
#include <iostream>
#include <fstream>
#include "clsScreen.h"
#include "Global.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsUtility.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	static bool _login()
	{
		bool loginFailed = false;
		short loginCountFailed = 0;
		string userName, password;

		do
		{
			if (loginFailed)
			{
				loginCountFailed++;

				cout << "\nInvalid Username/Password!\n";
				cout << "You have " << 3 - loginCountFailed << " trial(s) left to login.\n\n";
			}

			if (loginCountFailed == 3)
			{
				cout << "You are locked after 3 failed trails\n";
				currentUser.sendEmail(" Unsuccessful Login Attempts Detected on Your Account", "We noticed three unsuccessful login attempts on your account.");
				return false;
			}

			cout << "Enter username: ";
			userName = clsInputValidate::readString();
			cout << "Enter password: ";
			password = clsInputValidate::readString();

			// Global variable for all the system
			currentUser = clsUser::find(userName, password);

			loginFailed = currentUser.isEmpty();

		} while (loginFailed);

		currentUser.recordLogin();

		clsMainScreen::showMainMenuScreen();
		return true;
	}

public:
	static bool showLoginScreen()
	{
		system("cls");
		_drawScreenHeader("\t     Login Screen");
		return _login();
	}
};