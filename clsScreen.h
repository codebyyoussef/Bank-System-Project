
#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{
protected:

	static void _ShowDateAndLoggedInUser()
	{
		cout << "\t\t\t\t\tUser: " << currentUser.userName << "\n";
		cout << "\t\t\t\t\tDate: " << clsDate::dateToString(clsDate::getCurrentDate()) << "\n\n";
	}

	static void _drawScreenHeader(string title, string subTitle = "")
	{
		cout << "\t\t\t\t\t------------------------------------\n";
		cout << "\t\t\t\t\t" << title << "\n";
		if (subTitle != "")
		{
			cout << "\t\t\t\t\t" << subTitle << "\n";
		}
		cout << "\t\t\t\t\t------------------------------------\n";
		_ShowDateAndLoggedInUser();
	}

	static bool _checkAccessRights(clsUser::enPermissions permission)
	{
		if (!currentUser.checkAcessPermission(permission))
		{
			cout << "\t\t\t\t\t------------------------------------\n";
			cout << "\t\t\t\t\t Access Denied! Contact Your Admin\n";
			cout << "\t\t\t\t\t------------------------------------\n\n";
			return false;
		}
		else
		{
			return true;
		}
	}
};

