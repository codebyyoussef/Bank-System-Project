#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsUsersLoginRecordsScreen : protected clsScreen
{
private:
	static void _printUserLoginRecordDetails(clsUser::stUserLoginRecord userLoginRecord)
	{
		cout << "\t| " << setw(25) << left << userLoginRecord.dateTime;
		cout << "| " << setw(20) << left << userLoginRecord.userName;
		cout << "| " << setw(20) << left << userLoginRecord.password;
		cout << "| " << setw(10) << left << userLoginRecord.permissions;
	}
	
public:
	static void showUsersLoginRecordsScreen()
	{
		if (!_checkAccessRights(clsUser::enPermissions::pShowUsersLoginRecords))
		{
			return;
		}

		vector<clsUser::stUserLoginRecord> vUsersLoginRecords = clsUser::readUsersLoginRecordsFromFile();
		string title = "     Users Login Records Screen";
		string subTitle = "\t   (" + to_string(vUsersLoginRecords.size()) + ") Record(s).";
		_drawScreenHeader(title, subTitle);

		cout << "\t_______________________________________________________________________________________________\n\n";
		cout << "\t| " << setw(25) << left << "Date/Time";
		cout << "| " << setw(20) << left << "Username";
		cout << "| " << setw(20) << left << "Password";
		cout << "| " << setw(10) << left << "Permissions";
		cout << "\n\t_______________________________________________________________________________________________\n\n";
		if (vUsersLoginRecords.size() == 0)
		{
			cout << "\tNo login records are available in the system!\n";
		}
		else
		{
			for (const clsUser::stUserLoginRecord& userLoginRecord : vUsersLoginRecords)
			{
				_printUserLoginRecordDetails(userLoginRecord);
				cout << "\n";
			}
		}
		cout << "\n\t_______________________________________________________________________________________________\n\n";
	}
};

